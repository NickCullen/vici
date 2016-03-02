#include "Engine.h"
#include "Renderer.h"

VEngine::VEngine()
{
	
}

VEngine::~VEngine()
{

}

bool VEngine::Init(int argc, const char** argv)
{
	if (!VRenderer::Init())
		return false;


	return true;
}