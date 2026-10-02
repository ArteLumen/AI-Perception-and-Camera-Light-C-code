# Unreal Engine 5 C++ AI Perception & Camera System

A modular Unreal Engine 5 project showcasing advanced C++ implementation of **AI Perception**, **Behavior Trees**, **Dynamic Searchlight/Camera systems**, and a **smooth Third-Person Character control setup**.

---

## 🚀 Key Features

* **AI Perception (Sight):** Utilizes `UAIPerceptionComponent` and `UAISenseConfig_Sight` to detect players within a defined cone angle and radius.
* **Behavior Tree & Blackboard Integration:** Manages AI state transitions (Patrol vs. Chase/Alert) dynamically using custom tasks and blackboard keys (`TargetActor`, `HasLineOfSight`, `PatrolLocation`).
* **Dynamic Searchlight Feedback:** Integrates a `USpotLightComponent` on the AI controller that changes color automatically based on perception state (**Green** for Patrol, **Red** for Alert).
* **Advanced Third-Person Camera:** Features smooth camera lag (`bEnableCameraLag`), dynamic distance adjustment, and smooth FOV interpolation (`FMath::FInterpTo`) for zooming/aiming mechanics.
* **Enhanced Input Support:** Clean input mapping for movement and look axes.

---

## 🛠️ Code Structure

### 1. Character & Camera System (`AMyCharacter`)
* Manages `USpringArmComponent` and `UCameraComponent`.
* Implements runtime FOV and arm-length interpolation for smooth aiming/zooming.
* Configures character movement rotation relative to control yaw.

### 2. AI Controller & Perception (`AMyAIController`)
* Sets up sight configuration parameters (sight radius, lose sight radius, peripheral vision angle).
* Binds `OnTargetPerceptionUpdated` to react in real-time when the player enters or leaves sight.
* Dynamically updates the `USpotLightComponent` color and behavior tree blackboard keys.

### 3. Custom Behavior Tree Tasks (`UBTTask_GetRandomLocation`)
* Interfaces with Unreal Engine's `UNavigationSystemV1` to query reachable random points on the NavMesh within a specified radius for AI patrolling.

---

## 📂 Project Architecture

```text
Source/
└── YourGameName/
    ├── Characters/
    │   ├── MyCharacter.h
    │   └── MyCharacter.cpp
    ├── AI/
    │   ├── MyAIController.h
    │   ├── MyAIController.cpp
    │   ├── BTTask_GetRandomLocation.h
    │   └── BTTask_GetRandomLocation.cpp
    └── YourGameName.h / .cpp
