/*
 * Copyright © 2009-2020 Frictional Games
 *
 * This file is part of Amnesia: The Dark Descent.
 *
 * Amnesia: The Dark Descent is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Amnesia: The Dark Descent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Amnesia: The Dark Descent.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ED_WINDOW_EMITTERS_H
#define ED_WINDOW_EMITTERS_H

#include "../common/EdWindowHandler.h"

class iEditor;
class cEdEditPaneParticleEmitter;
class cEdObjParticleEmitter;


//-------------------------------------------------------------

class cEdWindowEmitters : public iEdCreatorPane
{
public:
	cEdWindowEmitters(iEdEditMode*);
	~cEdWindowEmitters();

	void SelectEntry(int alIdx);

protected:
	void OnCreateLayout();
	void OnUpdate();
	void OnReset();

	void OnWorldLoad();
	void OnWorldAddRemObject();

	bool WindowSpecificInputCallback(iEdInput* apInput);

	bool New_OnPressed(iWidget*, const cGuiMessageData&);
	kGuiCallbackDeclarationEnd(New_OnPressed);

	bool Copy_OnPressed(iWidget*, const cGuiMessageData&);
	kGuiCallbackDeclarationEnd(Copy_OnPressed);

	bool Delete_OnPressed(iWidget*, const cGuiMessageData&);
	kGuiCallbackDeclarationEnd(Delete_OnPressed);

	bool mbEmittersUpdated;
	cEdInputEnum* mpInpEmitters;
	std::vector<cEdObjParticleEmitter*> mvEmitters;

	cWidgetButton* mpBNewEmitter;
	cWidgetButton* mpBCopyEmitter;
	cWidgetButton* mpBDeleteEmitter;
};

//-------------------------------------------------------------


#endif // ED_WINDOW_EMITTERS_H
