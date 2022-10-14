#include "Object.h"

Object::Object()
{
	texture = new Texture();
	shouldDraw = true;
}

Object::Object(Texture* texture)
{
	this->texture = texture;
	shouldDraw = true;
}

void Object::update()
{
}
