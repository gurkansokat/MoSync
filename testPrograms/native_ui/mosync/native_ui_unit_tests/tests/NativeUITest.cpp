/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/*
 * NativeUITest.cpp
 *
 * This file contains general smoke tests for Native UI.
 * It checks for reasonable return codes on bad input.
 *
 *  Created on: Mar 14, 2011
 *      Author: fmattias
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <ma.h>

#include <IX_WIDGET.h>

#include <Testify/testify.hpp>

class NativeUITest
: public Testify::TestCase
{
public:
	NativeUITest()
	{
		addTest( bind( &NativeUITest::createBadWidget, this ),
				"Creating a bad widget." );

		addTest( bind( &NativeUITest::useBadHandle, this ),
				"Using a bad handle." );

		addTest( bind( &NativeUITest::addWidgetToNonLayout, this ),
				"Add a widget to a non layout." );

		addTest( bind( &NativeUITest::addWidgetToItself, this ),
				"Try to add a widget to itself." );
	}

	/**
	 * This test checks that
	 */
	void createBadWidget()
	{
		TESTIFY_ASSERT_EQUAL( maWidgetCreate( "BadWidget" ), MAW_RES_INVALID_TYPE_NAME );
	}

	/**
	 * This test asserts that functions behave correctly when they
	 * get a bad widget handle.
	 */
	void useBadHandle()
	{
		int badHandle = -512;

		TESTIFY_ASSERT_EQUAL( maWidgetSetProperty( badHandle, "property", "value" ), MAW_RES_INVALID_HANDLE );

		TESTIFY_ASSERT_EQUAL( maWidgetGetProperty( badHandle, "property", NULL, 0 ), MAW_RES_INVALID_HANDLE );

		TESTIFY_ASSERT_EQUAL( maWidgetDestroy( badHandle ), MAW_RES_INVALID_HANDLE );

		TESTIFY_ASSERT_EQUAL( maWidgetRemoveChild( badHandle ), MAW_RES_INVALID_HANDLE );

		TESTIFY_ASSERT_EQUAL( maWidgetScreenShow( badHandle ), MAW_RES_INVALID_HANDLE );
	}

	/**
	 * This test tries to add a widget to a non-layout widget.
	 */
	void addWidgetToNonLayout()
	{
		MAWidgetHandle label1 = maWidgetCreate( MAW_LABEL );
		TESTIFY_ASSERT( label1 >= 0 );

		MAWidgetHandle label2 = maWidgetCreate( MAW_LABEL );
		TESTIFY_ASSERT( label2 >= 0 );

		TESTIFY_ASSERT_EQUAL( maWidgetAddChild( label1, label2 ), MAW_RES_INVALID_LAYOUT );

		TESTIFY_ASSERT_EQUAL( maWidgetDestroy( label1 ), MAW_RES_OK );
		TESTIFY_ASSERT_EQUAL( maWidgetDestroy( label2 ), MAW_RES_OK );
	}

	/**
	 * This test tries to add a widget to itself as a child.
	 */
	void addWidgetToItself()
	{
		MAWidgetHandle layout = maWidgetCreate( MAW_RELATIVE_LAYOUT );
		TESTIFY_ASSERT( layout >= 0 );

		TESTIFY_ASSERT_EQUAL( maWidgetAddChild( layout, layout ), MAW_RES_ERROR );

		TESTIFY_ASSERT_EQUAL( maWidgetDestroy( layout ), MAW_RES_OK );
	}
};

static Testify::TestHook hook( new NativeUITest( ), "NativeUI" );

#endif /* SCREEN_H_ */
