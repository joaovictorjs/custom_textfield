#include "text_field.h"

TextField::TextField(wxWindow* parent,
                     const int id,
                     const wxPoint& pos,
                     const wxSize& size)
  : wxWindow(parent, id, pos, size, wxTRANSPARENT_WINDOW)
{
  Bind(wxEVT_PAINT, &TextField::on_paint, this);
  Bind(wxEVT_ERASE_BACKGROUND, &TextField::on_erase, this);
  Bind(wxEVT_CHAR, &TextField::on_char, this);
}

void
TextField::on_erase(wxEraseEvent& e)
{
  e.Skip(false);
}

void
TextField::on_char(wxKeyEvent& e)
{
}

void
TextField::on_paint(wxPaintEvent& e)
{
}
