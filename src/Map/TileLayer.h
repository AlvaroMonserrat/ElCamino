#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>

struct TileSet
{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
    public:
        virtual void Render();
        virtual void Update();

        TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tileset);

        inline TileMap GetTileMap(){ return m_Tilemap;}

    private:
        //Pixels size
        int m_TileSize;

        //Fila y Columna de Tiles en el mapa
        int m_RowCount, m_ColCount;

        //Mapa formado por id de tiles y capas
        TileMap m_Tilemap;

        //Lista de Conjunto de Cerámicas
        TilesetList m_Tilesets;
};

#endif // TILELAYER_H
