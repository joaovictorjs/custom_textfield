#include "text_field.h"

TextField::TextField(wxWindow *parent, const int id, const wxPoint &pos,
                     const wxSize &size)
    : wxWindow(parent, id, pos, size, wxTRANSPARENT_WINDOW) {
  cursor_x = 0;
  text_x = 0;
  text_y = (size.GetHeight() / 2) - (GetCharHeight() / 2);
  max = size.GetWidth();

  Bind(wxEVT_PAINT, &TextField::on_paint, this);
  Bind(wxEVT_ERASE_BACKGROUND, &TextField::on_erase, this);
  Bind(wxEVT_CHAR, &TextField::on_char, this);
}

void TextField::on_erase(wxEraseEvent &e) { e.Skip(false); }

void TextField::on_char(wxKeyEvent &e) {
  int code{e.GetKeyCode()};

  if (code == WXK_LEFT && cursor_pos > 0) {
    char c{text[cursor_pos - 1]};
    int cw{GetTextExtent(c).GetWidth()};
    cursor_pos--;

    if (cursor_x - cw < 0) {
      text_x += cw;
    } else {
      cursor_x -= cw;
    }
  }
  //
  //  if (code == WXK_RIGHT && cursor_pos < text.size()) {
  //    char c{ text[cursor_pos] };
  //    int cw{ GetTextExtent(c).GetWidth() };
  //    cursor_pos++;
  //
  //    if (cursor_x + cw > max) {
  //      text_x -= cw;
  //    } else {
  //      cursor_x += cw;
  //    }
  //  }

  if (code == WXK_SPACE || code >= 33 && code <= 126) {
    char c{static_cast<char>(code)};

    if (cursor_pos == 0) {
      text = c + text;
    } else if (cursor_pos != text.size()) {
      text =
          text.substr(0, cursor_pos) + c + text.substr(cursor_pos, text.size());
    } else {
      text += c;
    }

    cursor_pos++;
    int char_w{GetTextExtent(c).GetWidth()};
    int text_w{GetTextExtent(text).GetWidth()};

    if (cursor_pos == text.size()) {
      if (text_w > max) {
        text_x = max - text_w;
      }
      cursor_x = text_w - (text_x * -1);
    } else {
      std::string tmp{text.substr(0, cursor_pos)};
      int tmp_w{GetTextExtent(tmp).GetWidth()};
      int tmp_diff{tmp_w - (text_x * -1)};
      if (tmp_diff > max) {
        text_x = max - tmp_w;
      }
      cursor_x = tmp_w - (text_x *-1);
    }
  }

  // if (code == WXK_BACK && cursor_pos > 0 && text.size() > 0) {
  //   char c{ text[cursor_pos - 1] };
  //   text.erase(cursor_pos - 1, 1);
  //   cursor_pos--;
  // }

  //  if(code == WXK_DELETE && cursor_pos > 0 && text.size() > 0 && cursor_pos <
  //  text.size()){
  //    text.erase(cursor_pos, 1);
  //  }

  Refresh();
}

void TextField::on_paint(wxPaintEvent &e) {
  wxPaintDC dc{this};

  dc.SetBrush(*wxLIGHT_GREY);
  dc.SetPen(*wxTRANSPARENT_PEN);
  dc.DrawRectangle(wxPoint(0, 0), GetClientSize());

  dc.DrawText(text, text_x, text_y);

  dc.SetPen(*wxRED);
  dc.DrawLine(cursor_x, 0, cursor_x, GetClientSize().GetHeight());
}
