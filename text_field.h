#pragma once

#include <iostream>

#include <wx/dcclient.h>
#include <wx/graphics.h>
#include <wx/window.h>

class TextField : public wxWindow {
private:
  wxString text;

  int cursor_pos, text_x, text_y, cursor_x, max;

  void on_paint(wxPaintEvent &e);
  void on_char(wxKeyEvent &e);
  void on_erase(wxEraseEvent &e);

public:
  TextField(wxWindow *parent, const int id, const wxPoint &pos,
            const wxSize &size);
};
