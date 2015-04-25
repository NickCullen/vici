#include "ScriptableComponent.h"


ScriptableComponent::ScriptableComponent()
{

}

ScriptableComponent::~ScriptableComponent()
{

}

void ScriptableComponent::MyFunc()
{
	_Platform->LogString("ScriptableComponent::MyFunc");
}
