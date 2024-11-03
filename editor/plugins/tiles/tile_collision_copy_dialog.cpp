/**************************************************************************/
/*  tile_collision_copy_dialog.cpp                                        */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2024-present Redot Engine contributors                   */
/*                                          (see REDOT_AUTHORS.md)        */
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "tile_collision_copy_dialog.h"

#include "scene/gui/control.h"
#include "scene/gui/option_button.h"
#include "scene/gui/tree.h"

void TileCollisionCopyDialog::edit(Ref<TileSet> p_tile_set) {
	if (tile_set == p_tile_set) {
		return;
	}

	tile_set = p_tile_set;

	// Refresh the lists
	/*
		Vector<OcclusionLayerTileData> TileData::occluders, sized to fit `tile_set->get_occlusion_layers_count()`
	*/
	treeitem_physics->clear_children();
	for (int physics_layer = 0; physics_layer < tile_set->get_physics_layers_count(); physics_layer++) {
		TreeItem *new_physics_child = treeitem_physics->create_child();
		new_physics_child->set_text(0, vformat(TTR("Physics Layer %d"), physics_layer));
		new_physics_child->set_selectable(0, false);

		new_physics_child->set_selectable(1, false);
		new_physics_child->set_editable(1, true);
		new_physics_child->set_cell_mode(1, TreeItem::TreeCellMode::CELL_MODE_CHECK);
	}

	treeitem_occlusion->clear_children();
	for (int occlusion_layer = 0; occlusion_layer < tile_set->get_occlusion_layers_count(); occlusion_layer++) {
		TreeItem *new_occl_child = treeitem_occlusion->create_child();
		new_occl_child->set_text(0, vformat(TTR("Occlusion Layer %d"), occlusion_layer));
		new_occl_child->set_selectable(0, false);

		new_occl_child->set_selectable(1, false);
		new_occl_child->set_editable(1, true);
		new_occl_child->set_cell_mode(1, TreeItem::TreeCellMode::CELL_MODE_CHECK);
	}
}

TileCollisionCopyDialog::TileCollisionCopyDialog() {
	VBoxContainer *main_layout = memnew(VBoxContainer);
	add_child(main_layout);
	main_layout->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

	opt_src_layer = memnew(OptionButton);
	main_layout->add_child(opt_src_layer);

	tree_layers = memnew(Tree);
	tree_layers->set_v_size_flags(Control::SizeFlags::SIZE_EXPAND_FILL);
	tree_layers->set_columns(2);
	tree_layers->set_column_expand(0, true);
	tree_layers->set_column_expand(1, false);
	TreeItem *tree_layers_root = tree_layers->create_item();
	tree_layers->set_hide_root(true);
	main_layout->add_child(tree_layers);

	treeitem_occlusion = tree_layers->create_item(tree_layers_root);
	treeitem_occlusion->set_selectable(0, false);
	treeitem_occlusion->set_text(0, TTR("Occlusion Layers"));

	treeitem_physics = tree_layers->create_item(tree_layers_root);
	treeitem_physics->set_selectable(0, false);
	treeitem_physics->set_text(0, TTR("Physics Layers"));
}
