#include "text_field.h"

TextField::TextField(wxWindow* parent,
                     const int id,
                     const wxPoint& pos,
                     const wxSize& size)
  : wxWindow(parent, id, pos, size, wxTRANSPARENT_WINDOW)
{
  text = "";
  text_x = 0;
  text_y = (size.GetHeight() / 2) - (GetCharHeight() / 2);
  text_x = 0;
  cursor_pos = 0;
  cursor_x = 0;

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

    int cw{ GetTextExtent(c).GetWidth() };
    int tw{ GetTextExtent(text).GetWidth() };

    std::cout << "cw: " << cw << '\n'
              << "tw: " << tw << '\n'
              << "cursor_x: " << cursor_x << '\n'
              << "cursor_x + cw: " << cursor_x + cw << '\n'
              << "----------------------------------\n";

    if (tw > 100) {
      text_x -= cw;
    } else {
      text_x = 0;
    }

    if (cursor_x + cw > 99) {
      cursor_x = 99;
    } else {
      cursor_x += cw;
    }
  }

  if (code == WXK_BACK && cursor_pos > 0 && text.size() > 0) {
    char c{ text[cursor_pos - 1] };
    int tw{ GetTextExtent(text).GetWidth() };
    int cw{ GetTextExtent(c).GetWidth() };

    if (cursor_pos == text.size()) {
      if (text_x < 0) {
        text_x += cw;
      } else {
        cursor_x -= cw;
      }
    } else {
      // TODO: when cursor is not in the final
    }

    text.erase(cursor_pos - 1, 1);
    cursor_pos--;
  }

  if (code == WXK_LEFT && cursor_pos > 0) {
    char c{ text[cursor_pos - 1] };
    int cw{ GetTextExtent(c).GetWidth() };
    cursor_pos--;

    if (cursor_x - cw < 0) {
      text_x += cw;
    } else {
      cursor_x -= cw;
    }
  }

  Refresh();
}

void
TextField::on_paint(wxPaintEvent& e)
{
  wxPaintDC dc{ this };
  dc.SetPen(*wxRED);
  dc.SetBrush(*wxLIGHT_GREY);
  dc.DrawRectangle(wxPoint(0, 0), GetClientSize());

  dc.DrawText(text, text_x, text_y);

  dc.SetPen(*wxBLACK);
  dc.DrawLine(cursor_x, 0, cursor_x, GetClientSize().GetHeight());
}
