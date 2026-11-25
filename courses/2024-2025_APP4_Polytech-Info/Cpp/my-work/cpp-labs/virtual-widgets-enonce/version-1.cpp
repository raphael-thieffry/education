#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct canvas_t {
  virtual void draw(int x, int y, char t) = 0;
  virtual ~canvas_t() = default;
};

struct blittable_t {
  using blittable_ptr_t = std::unique_ptr<blittable_t>;
  virtual void blit(canvas_t &dst) const = 0;
  virtual ~blittable_t() = default;
  virtual blittable_ptr_t getUniquePtr() const = 0;
};

using blittable_ptr_t = std::unique_ptr<blittable_t>;

struct ascii_art_t : public canvas_t {
  ascii_art_t(int w, int h) : storage(w * h, ' '), width(w), height(h) {}

  virtual void draw(int x, int y, char t) { storage[x + y * width] = t; }

  void display(std::ostream &os){
    writeObjets();
    os << std::string(2 + width, '-') << "\n";
    for (int j = 0; j < height; ++j) {
      os << '|';
      for (int i = 0; i < width; ++i)
        os << storage[i + j * width];
      os << "|\n";
    }

    os << std::string(2 + width, '-') << "\n";
  }
  
  void add(blittable_ptr_t obj) { 
    stockObjets.push_back(std::move(obj)); //on peut aussi dupliquer le ptr grace à obj->getUniquePtr()
  }
  void add(const blittable_t &obj) { 
    //par lvalue
    stockObjets.push_back(obj.getUniquePtr());
  }
  void add(blittable_t&& obj) { 
    //par rvalue
    stockObjets.push_back(obj.getUniquePtr());
  }

  void writeObjets(){
    for(auto &obj : stockObjets){
      obj->blit(*this);
    }
  }

private:
  std::vector<blittable_ptr_t> stockObjets;
  std::vector<char> storage;
  int width, height;
};



//-------------
struct box_t : blittable_t {
  box_t(int px0, int py0, int px1, int py1, char t)
      : x0(px0), y0(py0), x1(px1), y1(py1), texture(t) {}

  void blit(canvas_t &dst) const override {
    for (int i = x0; i <= x1; ++i) {
      dst.draw(i, y0, texture);
      dst.draw(i, y1, texture);
    }

    for (int i = y0; i <= y1; ++i) {
      dst.draw(x0, i, texture);
      dst.draw(x1, i, texture);
    }
  }

  blittable_ptr_t getUniquePtr() const override {
    return std::make_unique<box_t>(*this);
  }

  int x0, y0, x1, y1;
  char texture;
};

struct label_t : blittable_t {
  label_t(int x, int y, std::string s) : x0(x), y0(y), text(std::move(s)) {}

  void blit(canvas_t &dst) const override {
    int x = x0;
    for (auto c : text)
      dst.draw(x++, y0, c);
  }

  blittable_ptr_t getUniquePtr() const override {
    return std::make_unique<label_t>(*this);
  }

  int x0, y0;
  std::string text;
};

struct button_t : blittable_t {
  button_t(int x, int y, std::string t, char texture)
      : text(x + 2, y + 1, t), shape(x, y, x + 3 + t.size(), y + 2, texture) {}

  void blit(canvas_t &dst) const override {
    shape.blit(dst);
    text.blit(dst);
  }

  blittable_ptr_t getUniquePtr() const override {
    return std::make_unique<button_t>(*this);
  }

  label_t text;
  box_t shape;
};


int main() {
  ascii_art_t drawing(25, 9);
  auto a = std::make_unique<button_t>(3, 3, "Hello World!", '~');
  drawing.add(std::move(a));
  drawing.add(button_t(3, 6, "Hello World!", '~'));
  drawing.display(std::cout);
}
