// Justyce Hickman, PA2, 11/10/24
#ifndef HELPERS_H
#define HELPERS_H
#include "playlist.h"
#include <fstream>
#include <dirent.h>
#include <cstdio>
void promptSongSelection();
void displayMainMenu();
void writePlaylistToFile(Playlist&);
void readData(ifstream&, Playlist&);
bool createNewPlaylist(const Playlist&, Playlist&);
bool playlistExists(string playlistName);
bool manageExistingPlaylists(const Playlist& all, Playlist& selected);
int getExistingPlaylists(string*);
void promptPlaylistSelection(string* existingPlaylists, int numPlaylists);
bool modifyPlaylist(Playlist& playlist, const Playlist&);
bool addSongToPlaylist(Playlist& playlist, const Playlist& all);
bool deleteSongFromPlaylist(Playlist& playlist);
bool deletePlaylist(Playlist&);
bool deletePlaylist2(Playlist&);
void getUserEntry(int&);
#endif
