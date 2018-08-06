#ifndef __CONFIGRAW_HPP
#define __CONFIGRAW_HPP

#include <iostream>
#include <string>
#include <fstream>

namespace cr
{
    /**
     * \brief swaps the byteorder of the given value
     */
    template<typename T>
    T swapByteOrder(T value)
    {
        unsigned char *v = static_cast<unsigned char*>(&value);

        switch(sizeof(T))
        {
            case 8:
                value = (v[0]<<56) | (v[1]<<48) | (v[2]<<40) | (v[3]<<32) |
                    (v[4]<<24) | (v[5]<<16) | (v[6]<<8) | v[7];
                break;

            case 4:
                value = (v[0]<<24) | (v[1]<<16) | (v[2]<<8) | v[3];
                break;

            case 2:
                value = (v[0]<<8) | v[1];
                break;

            case 1:
            default:
                break;
        }

        return value;
    }

    /**
     * \brief loads a series of T values into a given buffer
     * \param path Destination of the file to be read
     * \param buffer Pointer to an array where the read values are stored
     * \param size Number of values to be read
     * \param swap True if the byte order of the read values shall be swapped
    */
    template<typename T>
    void loadraw(
        std::string path, T *buffer, std::size_t size, bool swap = false)
    {
        std::ifstream fs;

        fs.open(path.c_str(), std::ofstream::in | std::ofstream::binary);

        if (!fs.is_open())
        {
            std::cerr << "Error while loading data: cannot open file!\n";
            return;
        }

        T value;
        for (std::size_t i = 0; i < size; i++)
        {
            if (fs.good())
            {
                fs.read(static_cast<char*>(&value), sizeof(T));
                if (swap) value = swapByteOrder(value);
                buffer[i] = value;
            }
            else
                std::cerr << "Error while loading data: read failed!\n";
        }
        fs.close();
    }
}
#endif