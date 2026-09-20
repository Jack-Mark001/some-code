#ifndef LYRIC_H
#define LYRIC_H

#include <QString>
#include <QList>

struct LyricLine {
    qint64 time = 0;      // 毫秒
    QString text;         // 歌词文本
};

class Lyric
{
public:
    Lyric();

    bool load(const QString &lrcPath);     // 读文件 + 解析
    bool isEmpty() const { return m_lines.isEmpty(); }
    int  count()   const { return m_lines.size(); }

    // 播放到 position(ms)，返回当前应显示的行号；没有返回 -1
    int indexAt(qint64 position) const;

    QString textAt(int index) const;       // 当前行
    QString prevText(int index) const;     // 上一行（可能为空）
    QString nextText(int index) const;     // 下一行（可能为空）

private:
    void parse(const QString &content);    // 解析
    QList<LyricLine> m_lines;              // 按时间排好序
};

#endif // LYRIC_H