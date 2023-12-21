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
  int code{ e.GetKeyCode() };

  if (code == WXK_LEFT && cursor_pos > 0) {
    cursor_pos--;
  }

  if (code == WXK_RIGHT && cursor_pos < text.size()) {
    cursor_pos++;
  }

  if (code == WXK_SPACE || code >= 33 && code <= 126) {
    char c{ static_cast<char>(code) };

    if (cursor_pos == 0) {
      text = c + text;
    } else if (cursor_pos != text.size()) {
      text =
        text.substr(0, cursor_pos) + c + text.substr(cursor_pos, text.size());
    } else {
      text += c;
    }

    cursor_pos++;
  }

  if (code == WXK_BACK && cursor_pos > 0 && text.size() > 0) {
    text.erase(cursor_pos - 1, 1);
    cursor_pos--;
  }

  if(code == WXK_DELETE && cursor_pos > 0 && text.size() > 0 && cursor_pos < text.size()){
    text.erase(cursor_pos, 1);
  }

  Refresh();
}

void
TextField::on_paint(wxPaintEvent& e)
{
  wxPaintDC dc{ this };

  dc.DrawText(text, 10, 10);
}
