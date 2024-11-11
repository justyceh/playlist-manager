// Justyce Hickman, PA2, 11/10/24
#ifndef LOADEDSONGS_H
#define LOADEDSONGS_H

#include "song.h"

class Playlist{
    Song *firstSong, *lastSong;
    int numberSongsLoaded;
    string name;

    //have a private method to check if song is already in playlist
    bool checkIfSongIsInPlaylist(const Song&);
    //have a private method to add a new song to end of playlist (this gets called from the + operator overload)
    void addNewSong(const Song&);
    //have a private method to delete song from end of list (this gets called from - operator overload)
    void deleteSong();
    public:
        //constructors and destructor
        Playlist();
        Playlist(Song*, Song*, int, string);
        Playlist(const Playlist&);
        ~Playlist();
        //getters
        string getName() const;
        int getNumSongsLoaded() const;
        Song* getFirstSong();
        Song* getLastSong();
        //setters
        void setFirstSong(Song*);
        void setLastSong(Song*);
        void setName(string);
        //adder for new song at specified index location
        void addNewSong(const Song&, int);
        //delete song from specific index location
        void deleteSong(int);
        //method for getting a song at index
        Song* getSongAtIndex(int) const;
        
        void displayLoadedSongs(bool=true)const;
        void displaySongsWithoutNum();
        Playlist& operator=(const Playlist&);

        friend ostream & operator << (ostream &out, const Playlist &p);
        
        void operator+(Song a);
        void operator-(int);
        bool check(const Song&);
};
#endif