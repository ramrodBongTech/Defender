#include "stdafx.h"
#include "Scene.h"

Scene::Scene(std::string name) :
m_alive(true),
m_title(name) 
{}

Scene::~Scene() {}

void Scene::start() { m_alive = true; }

void Scene::stop() { m_alive = false; }

std::string Scene::getTitle() { return m_title; }
