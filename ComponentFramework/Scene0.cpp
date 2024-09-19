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

bool Scene0::OnCreate()
{
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
			//Actor* a = (Actor*)actors["ActorCube"].get();
			//TransformComponent transform = a->GetComponent<TransformComponent>().get();
			////transform.orientation + 
			//Quaternion rotation = QMath::angleAxisRotation(5.0f, MATH::Vec3(1.0f,0.0f, 0.0f));
			//transform.orientation = rotation * transform.orientation;
			//std::cout << "We have a box" << std::endl;

			////a.

			///*Component* b = a.get();
			//ShapeComponent* c = (ShapeComponent*)b;
			//if (c->shapeType == ShapeType::box) {
			//	std::cout << "We have a box" << std::endl;
			//	auto d = (GEOMETRY::Box) c.shape;
			//}*/
			// 
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
			mouseEnabled = !mouseEnabled;
			Vec3 mouseCoords(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 0.0f);
			// TODO for Assignment 2: 
			// Get a ray pointing into the world, We have the x, y pixel coordinates
			// Need to convert this into world space to build our ray

			// Loop through all the actors and check if the ray has collided with them
			// Pick the one with the smallest positive t value
			for (auto it = actors.begin(); it != actors.end(); ++it) {
				Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it->second);
				Ref<TransformComponent> transformComponent = actor->GetComponent <TransformComponent>();
				Ref<ShapeComponent> shapeComponent = actor->GetComponent <ShapeComponent>();
				// TODO for Assignment 2: 
				// Transform the ray into the local space of the object and check if a collision occured
			}
		}
		break;

	default:
		break;
	}

	// mouse
	if (mouseEnabled) {
		if (sdlEvent.type == SDL_MOUSEMOTION) {
			int x = sdlEvent.motion.x;
			int y = sdlEvent.motion.y;
			// right +x | left -x | up -y | down +y
			MATH::Vec3 mouseVel = MATH::Vec3(x, y, 0.0f) - oldMousePos;
			MATH::Vec3 mouseAcc = mouseVel - oldMouseVel;
			printf("Mouse moved: x=%d\ty=%d\t\t xACC:%f.2\t yACC:%f.2\n", x, y, mouseAcc.x, mouseAcc.y);

			float rotationSpeed = 1.0f;
			MATH::Vec3 mouseSpeed = mouseVel * oldDeltaTime;
		

			if (mouseVel.x > 0) { // right
				cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(rotationSpeed, Vec3(0.0f, 1.0f, 0.0f)));
				camera->UpdateViewMatrix();
			} else if (mouseVel.x < 0) { // left
				cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(-rotationSpeed, Vec3(0.0f, 1.0f, 0.0f)));
				camera->UpdateViewMatrix();
			} else if (mouseVel.y < 0) { // up
				cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(rotationSpeed, Vec3(1.0f, 0.0f, 0.0f)));
				camera->UpdateViewMatrix();
			} else { // down
				cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(-rotationSpeed, Vec3(1.0f, 0.0f, 0.0f)));
				camera->UpdateViewMatrix();
			}

			// update oldMouse
			oldMousePos.set(x,y,0.0f);
			oldMouseVel = mouseVel;
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

