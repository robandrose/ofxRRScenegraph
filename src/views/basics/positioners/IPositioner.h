/*
 *  IPositioner.h
 *  BasicScreenObject_Test
 *
 *  Created by Patrick Meister on 26.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 *	This is an pure abstract virtual interface class.
 *  Subclasses of IPositioner _MUST_ implement all of the
 *  methods defined here.
 *  http://www.learncpp.com/cpp-tutorial/126-pure-virtual-functions-abstract-base-classes-and-interface-classes/
 */
#pragma once
#include "MathHelper.h"

class BasicScreenObject;

class IPositioner
{
public:
    virtual void restrict(BasicScreenObject* _object) = 0;
};