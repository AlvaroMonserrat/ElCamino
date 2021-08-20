#ifndef MAPPARSER_H
#define MAPPARSER_H


class MapParser
{
    public:
        bool Load();
        bool Clean();

    private:
        bool Parse(std::string id, std::string source);

    private:
        std::map<std::string, GameMap*> m_MapDict;
};

#endif // MAPPARSER_H
