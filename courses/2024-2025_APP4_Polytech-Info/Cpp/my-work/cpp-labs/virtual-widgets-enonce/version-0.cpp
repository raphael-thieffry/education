#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct canvas_t {
  virtual void draw(int x, int y, char t) = 0;
  virtual ~canvas_t() = default;
};

struct box_t {
  box_t(int px0, int py0, int px1, int py1, char t)
      : x0(px0), y0(py0), x1(px1), y1(py1), texture(t) {}

  void blit(canvas_t &dst) const {
    for (int i = x0; i <= x1; ++i) {
      dst.draw(i, y0, texture);
      dst.draw(i, y1, texture);
    }

    for (int i = y0; i <= y1; ++i) {
      dst.draw(x0, i, texture);
      dst.draw(x1, i, texture);
    }
  }

  int x0, y0, x1, y1;
  char texture;
};

struct label_t {
  label_t(int x, int y, std::string s) : x0(x), y0(y), text(std::move(s)) {}

  void blit(canvas_t &dst) const {
    int x = x0;
    for (auto c : text)
      dst.draw(x++, y0, c);
  }

  int x0, y0;
  std::string text;
};

struct button_t {
  button_t(int x, int y, std::string t, char texture)
      : text(x + 2, y + 1, t), shape(x, y, x + 3 + t.size(), y + 2, texture) {}

  void blit(canvas_t &dst) const {
    shape.blit(dst);
    text.blit(dst);
  }

  label_t text;
  box_t shape;
};

struct ascii_art_t : public canvas_t {
  ascii_art_t(int w, int h) : storage(w * h, ' '), width(w), height(h) {}

  virtual void draw(int x, int y, char t) { storage[x + y * width] = t; }

  void display(std::ostream &os) const {
    os << std::string(2 + width, '-') << "\n";
    for (int j = 0; j < height; ++j) {
      os << '|';
      for (int i = 0; i < width; ++i)
        os << storage[i + j * width];
      os << "|\n";
    }

    os << std::string(2 + width, '-') << "\n";
  }

private:
  std::vector<char> storage;
  int width, height;
};

int main() {
  button_t b(3, 3, "Hello World!", '~');
  ascii_art_t drawing(25, 9);

  b.blit(drawing);

  drawing.display(std::cout);

  //tests

  ascii_art_t drawing2(25, 9);
  label_t l(3+2, 3+3, "Hello World!");
  box_t b2(3, 1, 3 + 3 + 11, 3 + 2, '~');
  b2.blit(drawing2);
  l.blit(drawing2);
  drawing2.display(std::cout);

  return 0;
}
