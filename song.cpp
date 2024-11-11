// Justyce Hickman, PA2, 11/10/24
#include "song.h"

//constructors and destructor
Song::Song(){
    title = "FakeSong";
    artist = "FakeArtist";
    nextSong = nullptr;
}
Song::Song(string a, string t){
    artist = a;
    title = t;
    nextSong = nullptr;
}
Song::Song(const Song& rhs){
    artist = rhs.artist;
    title = rhs.title;
    nextSong = nullptr;
}
//setters
void Song::setArtist(string a){
    artist = a;
}
void Song::setTitle(string t){
    title = t;
}
void Song::setNextSong(Song* newSong){
    nextSong = newSong;
}
//getters
Song* Song::getNextSong(){
    return nextSong;
}
string Song::getArtist() const{
    return artist;
}
string Song::getTitle() const{
    return title;
}
Song& Song::operator=(const Song& rhs){
    title = rhs.title;
    artist = rhs.artist;
    nextSong = rhs.nextSong;
    //copy code body from copy constructor
    //have a return *this
    return *this;
}
Song::~Song(){

}


