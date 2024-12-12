#include "TextEditor.h"
#include <bits/stdc++.h>

using namespace std;

list<char>::iterator cursor;
list<char> buffer;
string copyText;

TextEditor::TextEditor() {
    // TODO: 用空文本初始化
    buffer.clear();
    copyText.clear();
    cursor = buffer.begin();
};

void TextEditor::addText(const string& text) {
    // TODO: 将 text 添加到光标所在位置
    for (char c : text) {
        cursor = buffer.insert(cursor, c);
        cursor++;
    }
}

void TextEditor::deleteText(int length) {
    // TODO: 删除光标左边 length 个字符
    while (length > 0 && cursor != buffer.begin()) {
        cursor--;
        cursor = buffer.erase(cursor);
        length--;
    }
}

void TextEditor::moveCursor(int steps) {
    // TODO: 将光标向左向右移动
    if (steps > 0) {
        while (steps > 0 && cursor != buffer.end()) {
            cursor++;
            steps--;
        }
    } else {
        while (steps < 0 && cursor != buffer.begin()) {
            cursor--;
            steps++;
        }
    }
}

void TextEditor::copy(int length) {
    // TODO: 复制光标左侧 length 个字符
    copyText.clear();
    auto it = cursor;
    while (length > 0 && it != buffer.begin()) {
        it--;
        copyText.push_back(*it);
        length--;
    }
    reverse(copyText.begin(), copyText.end());
}

void TextEditor::paste() {
    // TODO: 在光标处添加上一次复制的文本
    for (char ch : copyText) {
        cursor = buffer.insert(cursor, ch);
        cursor++;
    }
}

void TextEditor::print() {
    // TODO: 输出当前编辑器内容
    for (char ch : buffer) {
        cout << ch;
    }
    cout << endl;
}