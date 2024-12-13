#include "TextEditor_string.h"
#include <iostream>

using namespace std;

TextEditor::TextEditor() {
    cur_pos = 0;
    text_buffer = "";
    copy_text = "";
};

void TextEditor::addText(const string& text) {
    // TODO: 将 text 添加到光标所在位置
    text_buffer.insert(cur_pos, text);
    cur_pos += text.size();
}

void TextEditor::deleteText(int length) {
    // TODO: 删除光标左边 length 个字符
    int len = cur_pos > length ? length : cur_pos;
    text_buffer.erase(cur_pos - len, len);
    cur_pos -= len;
}

void TextEditor::moveCursor(int steps) {
    // TODO: 将光标向左向右移动
    cur_pos += steps;
    if (cur_pos < 0) {
        cur_pos = 0;
    } else if (cur_pos > text_buffer.size()) {
        cur_pos = text_buffer.size();
    }
}

void TextEditor::copy(int length) {
    // TODO: 复制光标左侧 length 个字符
    int len = cur_pos > length ? length : cur_pos;
    copy_text = text_buffer.substr(cur_pos - len, len);
}

void TextEditor::paste() {
    // TODO: 在光标处添加上一次复制的文本
    text_buffer.insert(cur_pos, copy_text);
    cur_pos += copy_text.size();
}

void TextEditor::print() {
    // TODO: 输出当前编辑器内容
    std::cout << text_buffer << std::endl;
}