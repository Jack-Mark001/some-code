#include "lyrics.h"
#include <QFile>
#include <QRegularExpression>
#include <algorithm>

Lyric::Lyric() {}

bool Lyric::load(const QString &lrcPath)
{
    m_lines.clear();
    if (lrcPath.isEmpty())
        return false;

    QFile file(lrcPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QString content = QString::fromUtf8(file.readAll());
    file.close();

    parse(content);
    return !m_lines.isEmpty();
}

void Lyric::parse(const QString &content)
{
    // 只用来把 tag 里的时间提取出来
    QRegularExpression re(R"(\[(\d{1,2}):(\d{2})\.(\d{2,3})\])");

    for (const QString &raw : content.split('\n')) {
        QString line = raw.trimmed();
        if (line.isEmpty()) continue;

        // === 按 ']' 分隔 ===
        int end = line.indexOf(']');
        if (end < 0) continue;

        QString tag  = line.left(end + 1);            // "[00:17.00]"
        QString text = line.mid(end + 1).trimmed();   // "还没来得及习惯"

        if (text.isEmpty()) continue;

        // 从 tag 解析时间
        QRegularExpressionMatch m = re.match(tag);
        if (!m.hasMatch()) continue;

        int min = m.captured(1).toInt();
        int sec = m.captured(2).toInt();
        QString msStr = m.captured(3);
        int ms = msStr.toInt();
        if (msStr.length() == 2) ms *= 10;   // "50" → 500ms

        qint64 time = (min * 60 + sec) * 1000 + ms;

        m_lines.append({time, text});
    }

    // 按时间排序（同时间的保持原顺序）
    std::stable_sort(m_lines.begin(), m_lines.end(),
                     [](const LyricLine &a, const LyricLine &b) { return a.time < b.time; });
}

int Lyric::indexAt(qint64 position) const
{
    if (m_lines.isEmpty()) return -1;

    // 找"time <= position"的最后一行
    int idx = -1;
    for (int i = 0; i < m_lines.size(); ++i) {
        if (m_lines[i].time <= position)
            idx = i;
        else
            break;
    }
    return idx;
}

QString Lyric::textAt(int index) const
{
    if (index < 0 || index >= m_lines.size()) return QString();
    return m_lines[index].text;
}

QString Lyric::prevText(int index) const
{
    if (index - 1 < 0 || index - 1 >= m_lines.size()) return QString();
    return m_lines[index - 1].text;
}

QString Lyric::nextText(int index) const
{
    if (index + 1 < 0 || index + 1 >= m_lines.size()) return QString();
    return m_lines[index + 1].text;
}