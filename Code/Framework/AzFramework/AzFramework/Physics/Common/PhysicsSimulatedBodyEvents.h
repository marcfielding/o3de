/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <AzCore/EBus/Event.h>
#include <AzFramework/Physics/Common/PhysicsTypes.h>

namespace AzPhysics
{
    struct CollisionEvent;
    struct TriggerEvent;

    namespace SimulatedBodyEvents
    {
        //! Collision Events for Simulated bodies.
        //! OnCollisionBegin is when two bodies start to collide. Will always be triggered before OnCollisionPersist and OnCollisionEnd.
        //! OnCollisionPersist is when two bodies continue to collide. Can only be triggered after OnCollisionBegin and before OnCollisionEnd.
        //! OnCollisionEnd is when two bodies stop colliding. Will always be triggered after OnCollisionBegin and OnCollisionPersist.
        //! The SimulatedBodyHandle passed in the event will match CollisionEvent::m_bodyHandle1, CollisionEvent::m_bodyHandle2 will be the other body involved.
        //! @note The CollisionEvent is only valid for the duration of the callback.
        //! This may fire multiple times per frame.
        using OnCollisionBegin = AZ::Event<SimulatedBodyHandle, const CollisionEvent&>;

        //! see OnCollisionBegin
        using OnCollisionPersist = AZ::Event<SimulatedBodyHandle, const CollisionEvent&>;

        //! see OnCollisionBegin
        using OnCollisionEnd = AZ::Event<SimulatedBodyHandle, const CollisionEvent&>;

        //! Trigger Events for Simulated bodies.
        //! OnTriggerEnter is when a body enters a trigger.
        //! OnTriggerExit is when a body leaves a trigger. Will only be triggered after OnTriggerEnter.
        //! These events will be triggered on both the trigger body and the body that entered/exited the trigger.
        //! The SimulatedBodyHandle passed will be the body that the handler is registered to, which can be the Trigger or Other body.
        //! @note The TriggerEvent is only valid for the duration of the callback.
        //! This may fire multiple times per frame.
        using OnTriggerEnter = AZ::Event<SimulatedBodyHandle, const TriggerEvent&>;

        //! see OnTriggerEnter
        using OnTriggerExit = AZ::Event<SimulatedBodyHandle, const TriggerEvent&>;

        //! Helper to register a Collision Event handler.
        //! @param sceneHandle A handle to the scene that owns the simulated body.
        //! @param bodyHandle A handle to the simulated body.
        //! @param handler The handle to register.
        void RegisterOnCollisionBeginHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle,
            OnCollisionBegin::Handler& handler);

        //! see RegisterOnCollisionBeginHandler
        void RegisterOnCollisionPersistHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle,
            OnCollisionPersist::Handler& handler);

        //! see RegisterOnCollisionBeginHandler
        void RegisterOnCollisionEndHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle,
            OnCollisionEnd::Handler& handler);

        //! Helper to register a Trigger Event handler.
        //! @param sceneHandle A handle to the scene that owns the simulated body.
        //! @param bodyHandle A handle to the simulated body.
        //! @param handler The handle to register.
        void RegisterOnTriggerEnterHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle,
            OnTriggerEnter::Handler& handler);

        //! see RegisterOnTriggerEnterHandler
        void RegisterOnTriggerExitHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle,
            OnTriggerExit::Handler& handler);
    } // namespace SimulatedBodyEvents
}