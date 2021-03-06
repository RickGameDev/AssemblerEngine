/*****************************************************************//**
 * @file   imgui.h
 * @ingroup api_group
 * @brief  Immediate Graphical User Interface API for creating engine widgets or drawing application UI
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */

#pragma once

#include <core/types.h>

struct ae_window;

/** /brief Viewport flags for enabling features of a viewport */
enum ae_imgui_viewport_flags
{
	AE_VIEWPORT_DOCKABLE =	(1 << 0),
	AE_VIEWPORT_DOCK =		(1 << 1),
	AE_VIEWPORT_FLOATING =	(1 << 2)
};

/** @brief ImGui API struct containing function pointers to draw GUI*/
struct ae_imgui_api
{
	void (*init)(struct ae_window* window);
	void (*start_frame)();
	void (*end_frame)();
	void (*start_viewport)(const char* name);
	void (*end_viewport)();
	void (*start_menu)();
	void (*end_menu)();
	void (*start_button)();
	void (*end_button)();

	void (*styles_push_size)(vec2 size);
	void (*styles_pop_size)();
	void (*styles_push_padding)(vec4 padding);
	void (*styles_pop_padding)();
	void (*styles_push_margin)(vec4 margin);
	void (*styles_pop_margin)();
	void (*styles_push_background_color)(vec4 color);
	void (*styles_pop_background_color)();
};

/**@}*/
