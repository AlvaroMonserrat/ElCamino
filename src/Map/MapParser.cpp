#include "MapParser.h"
#include "StateGame.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    return Parse("map", "assets/maps/etapa2.tmx");
}

bool MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++)
        it->second = nullptr;

    m_MapDict.clear();
}

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
    {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;

    //Ancho del mapa en tiles
    root->Attribute("width", &colcount);

    //Alto del mapa en tiles
    root->Attribute("height", &rowcount);

    //Tamaño de un tile
    root->Attribute("tilewidth", &tilesize);

    //TODO: Aceptar tiles no cuadrados
    //root->Attribute("tileheight", &tileheight);


    // Parse Tile sets, Obtener del archivo xml la data de los tile sets.
    TilesetList tilesets;
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }

    }

    // Parse Layers
    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);

            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;

    return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    TileSet tileset;

    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;

    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    xmlTileset->Attribute("spacing", &tileset.Spacing);
    xmlTileset->Attribute("margin", &tileset.Margin);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data;

    for(TiXmlElement* e = xmlLayer->FirstChildElement(); e!=nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for(int row = 0; row < rowcount; row++)
    {
        for(int col = 0; col < colcount; col++)
        {
            getline(iss, id, ',');
            if(id.compare("39") == 0)
            {
                //std::cout << "col:" << col  << " row:" << row << std::endl;
                //std::cout << "x:" << col*tilesize  << " y:" << row*tilesize << std::endl;
                StateGame::GetInstance()->setStartZone(col*tilesize, row*tilesize, tilesize, tilesize);
            }

            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good())
                break;
        }
    }

    std::cout << tilemap.size();

    //TileSize:: Tamaño de la cerámica
    //ColCount: Ancho del mapa en tiles
    //RowCount: Alto del mapa en tiles
    //tilemap: mapa de Tile ID.
    //tileSets: Conjunto de cerámicas
    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}
