#include "TextEditor.h"
#include <bits/stdc++.h>

using namespace std;

TextEditor::TextEditor() {
    // TODO: 用空文本初始化
    cursor = text.begin();
    copiedText = "";
};

void TextEditor::addText(const string& text) {
    // TODO: 将 text 添加到光标所在位置
    for (char c : text) {
        this->text.insert(cursor, c);
    }
}

void TextEditor::deleteText(int length) {
    // TODO: 删除光标左边 length 个字符
    while (length && cursor != text.begin()) {
        cursor = prev(cursor);
        cursor = text.erase(cursor);
        length--;
    }
}

void TextEditor::moveCursor(int steps) {
    // TODO: 将光标向左向右移动
    if (steps > 0) {
        while (steps && cursor != text.end()) {
            cursor = next(cursor);
            steps--;
        }
    } else {
        steps = -steps;
        while (steps && cursor != text.begin()) {
            cursor = prev(cursor);
            steps--;
        }
    }
}

void TextEditor::copy(int length) {
    // 复制光标左边 length 个字符
    copiedText.clear();  // 清空之前复制的内容
    auto it = cursor;
    while (length && it != text.begin()) {
        it = prev(it);
        copiedText.insert(copiedText.begin(), *it);  // 插入复制的字符
        length--;
    }
}

void TextEditor::paste() {
    // 在光标位置粘贴复制的文本
    for (char c : copiedText) {
        text.insert(cursor, c);  // 插入复制的字符
    }
}

void TextEditor::print() {
    // 输出当前文本
    for (char c : text) {
        std::cout << c;
    }
    std::cout << std::endl;
}