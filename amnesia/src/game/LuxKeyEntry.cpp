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

// generated by Fast Light User Interface Designer (fluid) version 1.0110

#include "LuxKeyEntry.h"
#define kTranslate(sCategory, sEntry) cString::To8Char(mpEngine->GetResources()->Translate(sCategory, sEntry)).c_str()

Fl_Input_Key::Fl_Input_Key(int X, int Y, int W, int H, const char *l ): Fl_Input(X,Y,W,H,l) {
}

int Fl_Input_Key::handle(int event) {
  switch (event) {
  case FL_KEYBOARD:
    if (Fl::event_key() == FL_Tab) {
      return Fl_Input::handle(event);
    } else {
      return handle_key();
    }
  case FL_PASTE:
    return handle_paste();
  default:
    return Fl_Input::handle(event);
  }
}

int Fl_Input_Key::handle_key() {
  char ascii = Fl::event_text()[0];
  char sep[2] = { '-','0'};
  int del;
  if (Fl::compose(del)) {
    Fl::compose_reset();
    int len = size();
    int pos = position();
    int epos = mark();
    if (pos > epos) {
      pos = epos;
      epos = position();
    }
    //std::cout << "pos:" << pos << ":"<<epos<<"\n";
    if (((len -(epos -pos)) < 16/*19*/ && pos < 17/*20*/)
        && verifychar(ascii)) {
      //std::cout << "Inserting "<<ascii<<" @ "<<pos<<" Len " << len << "\n";
      ascii = toupper(ascii);
      /*if (pos == 4 || pos == 9 || pos == 14) {
        sep[1] = ascii;
        if ((epos-pos)<2) {
          epos = pos + 2;
        }
        replace(pos, epos, sep, 2);
      } else {
        replace(pos, epos, &ascii, 1);
      }*/
      replace(pos, epos, &ascii, 1);
    } else {
      return 1;
    }
  } else {
    return Fl_Input::handle(FL_KEYBOARD);
  }
  return 1;
}

int Fl_Input_Key::handle_paste() {
  const char *t = Fl::event_text();
  const char *e = t+Fl::event_length();
  if (!t || e <= t) return 1;
  std::string newtext;
  while (newtext.length() < 17/*20*/ && t < e) {
    if (verifychar(*t)) {
      newtext.append(1,toupper(*t));
      /*int len = newtext.length();
      if (len == 4 || len == 9 || len == 14) {
        newtext.append("-");
      }*/
    }
    t++;
  }

  return replace(0,size(),newtext.c_str(),newtext.length());
}

bool Fl_Input_Key::verifychar(char key) {
  key = toupper(key);
  //std::cout << "Checking "<<key<<"\n";
  return ((key >= '1' && key <= '9')
	|| (key >= 'A' && key <= 'N')
	|| (key >= 'P' && key <= 'W')
	|| key == 'Z');
}

void InstallKeyEntry::cb_Exit_i(Fl_Button*, void*) {
  {
    //std::cout << "Exit pressed\n";
    exitflag = 1;
    Fl::delete_widget(keyentrydialog);
  };
}
void InstallKeyEntry::cb_Exit(Fl_Button* o, void* v) {
  ((InstallKeyEntry*)(o->parent()->user_data()))->cb_Exit_i(o,v);
}

void InstallKeyEntry::cb_Validate_i(Fl_Return_Button*, void*) {
  {
    //std::cout << "Setting Key";
    dest.assign(keyentry->value());
    exitflag = 0;
    Fl::delete_widget(keyentrydialog);
  };
}
void InstallKeyEntry::cb_Validate(Fl_Return_Button* o, void* v) {
  ((InstallKeyEntry*)(o->parent()->user_data()))->cb_Validate_i(o,v);
}

InstallKeyEntry::InstallKeyEntry(std::string &key, int &exitpressed): dest(key), exitflag(exitpressed) {
  Fl::scheme("plastic");
  { keyentrydialog = new Fl_Window(450, 100, "Amnesia - The Dark Descent");
    keyentrydialog->user_data((void*)(this));
    { new Fl_Box(10, 5, 425, 25, "Enter Serial Number Below");
    } // Fl_Box* o
    { keyentry = new Fl_Input_Key(10, 30, 430, 25, "Enter Serial Number Below");
      keyentry->box(FL_DOWN_BOX);
      keyentry->color((Fl_Color)FL_BACKGROUND2_COLOR);
      keyentry->selection_color((Fl_Color)FL_SELECTION_COLOR);
      keyentry->labeltype(FL_NO_LABEL);
      keyentry->labelfont(0);
      keyentry->labelsize(14);
      keyentry->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
      keyentry->align(FL_ALIGN_CENTER);
      keyentry->when(FL_WHEN_CHANGED);
    } // Fl_Input_Key* keyentry
    { Fl_Button* o = new Fl_Button(20, 65, 120, 25, "Exit");
      o->callback((Fl_Callback*)cb_Exit);
    } // Fl_Button* o
    { Fl_Return_Button* o = new Fl_Return_Button(285, 65, 140, 25, "Validate Serial");
      o->callback((Fl_Callback*)cb_Validate);
    } // Fl_Return_Button* o
    keyentrydialog->set_modal();
    keyentrydialog->size_range(450, 100, 450, 100);
    keyentrydialog->end();
  } // Fl_Window* keyentrydialog
  keyentry->value(dest.c_str());
  exitflag = 0;
}

void InstallKeyEntry::show(int argc, char*argv[]) {
  int x,y,w,h;
  Fl::screen_xywh(x,y,w,h);
  keyentrydialog->position((w-keyentrydialog->w())/2,(h-keyentrydialog->h())/2);
  keyentrydialog->show(argc,argv);
}

int Ask_Serial(std::string &serial) {
  int exitflag;
  char *argv[1] = {"./dummyprogram"};
  InstallKeyEntry *win = new InstallKeyEntry(serial,exitflag);

  win->show(0, argv);

  int ret = Fl::run();
  if (ret) {
    std::cout << "Error Creating Serial Dialog" << "\n";
  } else {
    //std::cout << "serial:" << serial << "\n";
    ret = exitflag;
  }
  return ret;
}
#if TEST

int main(int argc, char *argv[]) {
  std::string serial = "0000000000000000";
  Ask_Serial(serial);
  std::cout << "Serial Set to " << serial << "\n";
  return 0;
}
#endif
