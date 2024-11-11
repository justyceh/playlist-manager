// Justyce Hickman, PA2, 11/10/24
#ifndef SONG_H
#define SONG_H
#include <iostream>
using namespace std;
class Song{
    string title, artist;
    Song* nextSong;

    public:
        //constructors and destructors
        Song();
        Song(string, string);
        Song(const Song&);
        ~Song();
        //setters
        void setTitle(string);
        void setArtist(string);
        void setNextSong(Song*);

        //getters
        string getTitle() const;
        Song* getNextSong();
        string getArtist() const;
        Song& operator=(const Song&);

        friend ostream& operator<<(ostream &out, const Song &s);

        
};

#endif