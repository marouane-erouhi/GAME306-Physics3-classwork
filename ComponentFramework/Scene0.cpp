#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include <MMath.h>
#include "Debug.h"
#include "TransformComponent.h"
#include "MaterialComponent.h"
#include <QMath.h>
#include "XMLAssetManager.h"
#include "ShaderComponent.h"
#include "MeshComponent.h"
#include "ShapeComponent.h"
#include "QuadraticSolver.h"

bool Scene0::OnCreate()
{

/*	float a = 5.0f;
	float b = 2.0f;
	float c = -3.0f;

	GEOMETRY::QuadraticSolution soln = GEOMETRY::solveQuadratic(a, b, c);
	soln.print();
*/
	XMLAssetManager assetManager;
	// Make sure these names match the stuff in your xml file:
	std::vector<std::string> names{ 
		"ActorGameBoard" , "ActorChecker1", "ActorChecker2", 
		"ActorSkull", "ActorCube", "ActorMario"
	};
	for (const auto& name : names) {
		auto asset = assetManager.xmlAssets.find(name);
		actors[name] = asset->second;
	}
	camera = std::dynamic_pointer_cast<CameraActor>(assetManager.xmlAssets.find("Camera1")->second);
	light = std::dynamic_pointer_cast<LightActor>(assetManager.xmlAssets.find("Light1")->second);
	return true;
}

void Scene0::OnDestroy()
{
	actors.clear();
}


void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{
	Ref<TransformComponent> cameraTransform = camera->GetComponent <TransformComponent>();
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			// move left
			cameraTransform->SetTransform(
				cameraTransform->pos + QMath::rotate(MATH::Vec3(1, 0, 0), cameraTransform->GetOrientation()),
				cameraTransform->GetOrientation());
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			// move right
			cameraTransform->SetTransform(
				cameraTransform->pos + QMath::rotate(MATH::Vec3(-1, 0, 0), cameraTransform->GetOrientation()),
				cameraTransform->GetOrientation());
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
			// move camera forwards
			cameraTransform->SetTransform(
				cameraTransform->pos + QMath::rotate(MATH::Vec3(0, 0, 1), cameraTransform->GetOrientation()),
				cameraTransform->GetOrientation());
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			// move back
			cameraTransform->SetTransform(
				cameraTransform->pos + QMath::rotate(MATH::Vec3(0, 0, -1), cameraTransform->GetOrientation()),
				cameraTransform->GetOrientation());
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(2.0f, Vec3(0.0f, 1.0f, 0.0f)));
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(-2.0f, Vec3(0.0f, 1.0f, 0.0f)));
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(2.0f, Vec3(1.0f, 0.0f, 0.0f)));
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(-2.0f, Vec3(1.0f, 0.0f, 0.0f)));
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_M) {
			renderMeshes = !renderMeshes;
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_C) {
			renderCollisionShapes = !renderCollisionShapes;
		}

		break;
		
	case SDL_MOUSEBUTTONDOWN:
		if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
			HandleLeftClick(sdlEvent);
			//mouseEnabled = !mouseEnabled;
			//Vec3 mouseCoords(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 0.0f);
			//// TODO for Assignment 2: 
			//// Get a ray pointing into the world, We have the x, y pixel coordinates
			//// Need to convert this into world space to build our ray

			//// Loop through all the actors and check if the ray has collided with them
			//// Pick the one with the smallest positive t value
			//for (auto it = actors.begin(); it != actors.end(); ++it) {
			//	Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it->second);
			//	Ref<TransformComponent> transformComponent = actor->GetComponent <TransformComponent>();
			//	Ref<ShapeComponent> shapeComponent = actor->GetComponent <ShapeComponent>();
			//	// TODO for Assignment 2: 
			//	// Transform the ray into the local space of the object and check if a collision occured
			//}
		}
		break;

	default:
		break;
	}

	// enable/disable mouse look
	/*if (mouseEnabled) {
		if (sdlEvent.type == SDL_MOUSEMOTION) {
			MATH::Vec3 mouseVel = MATH::Vec3(sdlEvent.motion.xrel, sdlEvent.motion.yrel, 0.0f);

			float rotationSpeedX = 1.0f;
			float rotationSpeedY = 0.50f;

			if (mouseVel.x != 0) {
				cameraTransform->SetTransform(
					cameraTransform->pos,
					cameraTransform->GetOrientation() * QMath::angleAxisRotation(mouseVel.x * rotationSpeedX, Vec3(0.0f, 1.0f, 0.0f))
				);
				camera->UpdateViewMatrix();
			}

			if (mouseVel.y != 0) {
				cameraTransform->SetTransform(
					cameraTransform->pos,
					cameraTransform->GetOrientation() * QMath::angleAxisRotation(-mouseVel.y * rotationSpeedY, Vec3(1.0f, 0.0f, 0.0f))
				);
				camera->UpdateViewMatrix();
			}
		}
	}*/


}

void Scene0::HandleLeftClick(const SDL_Event& sdlEvent) {
	Vec3 mouseCoordsPixelSpace(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 0.0f);
	//mouseCoordsPixelSpace.print("pixel space");

	Matrix4 ndcToPixelSpace = MMath::viewportNDC(1280, 720);
	Matrix4 pixelToNdc = MMath::inverse(ndcToPixelSpace);

	// Scott is going to mess with our w component for perspective projection
	// So I'll flip to Vec4s
	Vec4 mouseCoordsNdcSpace = pixelToNdc * mouseCoordsPixelSpace;
	// Put mouse on front of NDC box (it's left handed)
	mouseCoordsNdcSpace.z = -1;
	//mouseCoordsNdcSpace.print("NDC space");

	// We need to read Song Ho's website on Scott's perspective matrix
	// https://songho.ca/opengl/gl_projectionmatrix.html
	// and Scott's website
	// https://scottfielder.com/ChalkTalk/projection.html

	Matrix4 cameraToNdc = camera->GetProjectionMatrix();
	Matrix4 ndcToCamera = MMath::inverse(cameraToNdc);
	Vec4 mouseCoordsCameraSpace = ndcToCamera * mouseCoordsNdcSpace;
	// The w coordinae gets messed up by the projection matrix
	// Song Ho has us covered here:
	// https://songho.ca/math/homogeneous/homogeneous.html
	//mouseCoordsCameraSpace.print("Camera space");

	// We live in 3D
	// So divide out the w component, such that w = 1
	mouseCoordsCameraSpace = VMath::perspectiveDivide(mouseCoordsCameraSpace);
	//mouseCoordsCameraSpace.print("Camera space with w divided out");

	Matrix4 worldToCameraSpace = camera->GetViewMatrix();
	Matrix4 cameraToWorldSpace = MMath::inverse(worldToCameraSpace);
	Vec4 mouseCoordsWorldSpace = cameraToWorldSpace * mouseCoordsCameraSpace;
	//mouseCoordsWorldSpace.print("World space");

	Vec3 rayStartWorldSpace = mouseCoordsWorldSpace;
	// Lucas says we can get the direction of the ray
	// by taking the difference between the mouse pos and the camera pos
	Vec3 rayDirWorldSpace = mouseCoordsWorldSpace - camera->GetComponent <TransformComponent>()->pos;
	rayDirWorldSpace = VMath::normalize(rayDirWorldSpace);

	GEOMETRY::Ray rayWorldSpace(rayStartWorldSpace, rayDirWorldSpace);

	// Loop through all the actors and check if the ray has collided with them
	// Pick the one with the smallest positive t value
	for (auto it = actors.begin(); it != actors.end(); ++it) {
		Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it->second);
		Ref<TransformComponent> transformComponent = actor->GetComponent <TransformComponent>();
		Ref<ShapeComponent> shapeComponent = actor->GetComponent <ShapeComponent>();
		// TODO for Assignment 2: 
		// Transform the ray into the local space (ie Paul Neale space) of the object and check if a collision occured
		if (shapeComponent->shapeType == ShapeType::sphere
			||
			shapeComponent->shapeType == ShapeType::cylinder
			||
			shapeComponent->shapeType == ShapeType::capsule
			) {
			// TODO FOR YOU
			// How do we handle actors with parents?
			Matrix4 paulNealeToWorldSpace = transformComponent->GetTransformMatrix();
			Matrix4 worldToPaulNealeSpace = MMath::inverse(paulNealeToWorldSpace);
			// Transform the start of the ray
			Vec3 rayStartPaulNealeSpace = worldToPaulNealeSpace * rayWorldSpace.start;
			// Transform the direction of the ray
			// Be careful, we don't want to translate the direction. 
			// Only rotate using quaternion
			Quaternion paulNealeToWorldSpaceRotation = transformComponent->GetOrientation();
			Quaternion worlToPaulNealeSpaceRotation = QMath::conjugate(paulNealeToWorldSpaceRotation);
			Vec3 rayDirPaulNealeSpace = QMath::rotate(rayWorldSpace.dir, worlToPaulNealeSpaceRotation);
			GEOMETRY::Ray rayPaulNealeSpace(rayStartPaulNealeSpace, rayDirPaulNealeSpace);
			// Shoot the ray at the sphere or cylinder
			rayInfo = shapeComponent->shape->rayIntersectionInfo(rayPaulNealeSpace);
			if (rayInfo.isIntersected) {
				std::cout << "You picked: " << it->first << '\n';
				pickedActor = actor; // make a member variable called pickedActor. Will come in handy later…
				haveClickedOnSomething = true; // make this a member variable too. Set it to false before we loop over each actor
			}

		}
	}

}

void Scene0::Update(const float deltaTime)
{
	oldDeltaTime = deltaTime;
}

void Scene0::Render() const
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_UNIFORM_BUFFER, camera->GetMatricesID());
	glBindBuffer(GL_UNIFORM_BUFFER, light->GetLightID());
	// Let it go
	glBindTexture(GL_TEXTURE_2D, 0);

	for (auto it = actors.begin(); it != actors.end(); ++it) {
		Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it->second);
		glUseProgram(actor->GetComponent<ShaderComponent>()->GetProgram());
		glUniformMatrix4fv(actor->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, actor->GetModelMatrix());
		glBindTexture(GL_TEXTURE_2D, actor->GetComponent<MaterialComponent>()->getTextureID());
		if (renderMeshes) {
			actor->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
		}
		if (renderCollisionShapes) {
			// Drawing the primitive geometry associated with the mesh to help debug ray intersects, culling, and collision detection
			actor->GetComponent<ShapeComponent>()->Render();
		}
	}
}

