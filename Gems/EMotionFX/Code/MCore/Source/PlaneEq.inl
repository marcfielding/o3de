/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


// check if the box is partially above the plane
MCORE_INLINE bool PlaneEq::PartiallyAbove(const AABB& box) const
{
    const AZ::Vector3 minVec = box.GetMin();
    const AZ::Vector3 maxVec = box.GetMax();
    const AZ::Vector3 testPoint(IsNegative(float(mNormal.GetX())) ? minVec.GetX() : maxVec.GetX(),
        IsNegative(static_cast<float>(mNormal.GetY())) ? minVec.GetY() : maxVec.GetY(),
        IsNegative(static_cast<float>(mNormal.GetZ())) ? minVec.GetZ() : maxVec.GetZ());

    return IsPositive(mNormal.Dot(testPoint) + mDist);
}


// check if the box is completely above the plane
MCORE_INLINE bool PlaneEq::CompletelyAbove(const AABB& box) const
{
    const AZ::Vector3 minVec = box.GetMin();
    const AZ::Vector3 maxVec = box.GetMax();
    const AZ::Vector3 testPoint(IsPositive(mNormal.GetX()) ? minVec.GetX() : maxVec.GetX(),
        IsPositive(mNormal.GetY()) ? minVec.GetY() : maxVec.GetY(),
        IsPositive(mNormal.GetZ()) ? minVec.GetZ() : maxVec.GetZ());

    return IsPositive(mNormal.Dot(testPoint) + mDist);
}
