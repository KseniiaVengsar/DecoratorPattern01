#include <iostream>
#include <string>
#include <algorithm>


class Text {
public:
    virtual void render(const std::string& text) const = 0;
    virtual ~Text() {}
};

class Paragraph : public Text {
public:
    void render(const std::string& text) const override {
        std::cout << "<p>" << text << "</p>";
    }
};

class Reversed : public Text {
public:
    void render(const std::string& text) const override {
        std::string reversed_text = text;
        std::reverse(reversed_text.begin(), reversed_text.end());
        std::cout << reversed_text;
    }
};

class Link : public Text {
public:
    void render(const std::string& text) const override {
        std::cout << "<a href=\"" << text << "\">" << text << "</a>";
    }
};

class TextDecorator : public Text {
protected:
    Text* text_;
public:
    TextDecorator(Text* text) : text_(text) {}
    virtual ~TextDecorator() { delete text_; }
    virtual void render(const std::string& text) const override {
        text_->render(text);
    }
};

class ParagraphDecorator : public TextDecorator {
public:
    ParagraphDecorator(Text* text) : TextDecorator(text) {}

    void render(const std::string& text) const override {
        std::cout << "<p>";
        TextDecorator::render(text);
        std::cout << "</p>";
    }
};

class ReversedDecorator : public TextDecorator {
public:
    ReversedDecorator(Text* text) : TextDecorator(text) {}

    void render(const std::string& text) const override {
        std::string reversed_text = text;
        std::reverse(reversed_text.begin(), reversed_text.end());
        TextDecorator::render(reversed_text);
    }
};


class LinkDecorator : public TextDecorator {
public:
    LinkDecorator(Text* text) : TextDecorator(text) {}

    void render(const std::string& url, const std::string& text) const {
        std::cout << "<a href=\"" << url << "\">";
        TextDecorator::render(text);
        std::cout << "</a>";
    }
};

int main() {
 
    Text* paragraph = new Paragraph();
    Text* reversed = new Reversed();
    Text* link = new Link();

    
    paragraph = new ParagraphDecorator(paragraph);
    reversed = new ReversedDecorator(reversed);
    link = new LinkDecorator(link);

   
    paragraph->render("Hello world");
    std::cout << std::endl;

    reversed->render("Hello world");
    std::cout << std::endl;

    link->render("https://netology.ru");
    std::cout << std::endl;


    delete paragraph;
    delete reversed;
    delete link;

    return 0;
}
