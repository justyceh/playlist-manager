// Justyce Hickman, PA2, 11/10/24
#include "playlist.h"

Playlist::Playlist(){
    firstSong = lastSong = nullptr; 
    numberSongsLoaded = 0;
    name = "Playlist";
}
Playlist::Playlist(Song* f, Song* l, int n, string nm){
    numberSongsLoaded = n;
    name = nm;
    if(f == nullptr){
        firstSong = lastSong = nullptr;
        return;
    }
    Song* temp = f;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
}


Playlist::Playlist(const Playlist& rhs){
    numberSongsLoaded = rhs.numberSongsLoaded;
    name = rhs.name;
    if(rhs.firstSong == nullptr){
        firstSong = lastSong = nullptr;
        return;
    }
    Song* temp = rhs.firstSong;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
}

Playlist::~Playlist(){
    Song* temp = firstSong;
    while(temp != nullptr){
        Song* removed = temp;
        temp = temp->getNextSong();
        delete removed;
    }
    firstSong = lastSong = nullptr;
}

string Playlist::getName() const{
    return name;
}
int Playlist::getNumSongsLoaded() const{
    return numberSongsLoaded;
}
Song* Playlist::getFirstSong(){
    return firstSong;
}
Song* Playlist::getLastSong(){
    return lastSong;
}

void Playlist::setName(string n){
    name = n;
}
void Playlist::setFirstSong(Song* f){
    firstSong = f;
}
void Playlist::setLastSong(Song* l){
    lastSong = l;
}
bool Playlist::checkIfSongIsInPlaylist(const Song& newSong){
    if(firstSong == nullptr){
        return false;
    }
    Song* temp = firstSong;
    while(temp != nullptr){
        if(temp->getTitle() == newSong.getTitle()){
            return true;
        }
        temp = temp->getNextSong();
    }
    return false;
}
void Playlist::addNewSong(const Song& newSong, int index){
    if(checkIfSongIsInPlaylist(newSong)){
        return;
    }
    if(index == numberSongsLoaded){
        addNewSong(newSong);
        return;
    }
    Song* currentSong = firstSong;
    Song* previousSong = nullptr;
    Song* temp = new Song;
    int count = 0;

    temp->setTitle(newSong.getTitle());
    temp->setArtist(newSong.getArtist());

    
    if(numberSongsLoaded == 0){
        firstSong = lastSong = temp;
        ++numberSongsLoaded;
        return;
    }
    
    while(count < index){
        if(count != index - 1 ){
            previousSong = currentSong;
            currentSong = currentSong->getNextSong();
        }
        else if(count == index - 1){
            if(index == 1){
                temp->setNextSong(currentSong);
                firstSong = temp;
                ++numberSongsLoaded;
                return;
            }
            else{
                temp->setNextSong(currentSong);
                previousSong->setNextSong(temp);
                ++numberSongsLoaded;
                return;
            }


        }
        ++count;
    }
}
void Playlist::deleteSong(){
    if(firstSong == lastSong){
        delete firstSong;
        firstSong = lastSong = nullptr;
        --numberSongsLoaded;
        return;
    }
    else if(firstSong == nullptr){
        return;
    }
    else{
        Song* temp = firstSong;
        firstSong = firstSong->getNextSong();
        delete temp;
        --numberSongsLoaded;
        return;
    }
}

void Playlist::deleteSong(int index){
    if(numberSongsLoaded == 1){
        deleteSong();
    }
    else if(index == 1){
        deleteSong();
    }
    else{

    Song* current = firstSong;
    Song* previous = nullptr;
    int songCount = 1;
    while(songCount < index){
        previous = current;
        current = current->getNextSong();
        ++songCount;
    }
    previous->setNextSong(current->getNextSong());
    delete current;
    --numberSongsLoaded;
    if(previous->getNextSong() == nullptr){
        lastSong = previous;
    }
    }
}
Song* Playlist::getSongAtIndex(int index) const{
    Song* temp = firstSong;
    int count = 1;
    while(temp != nullptr){
        if(count == index){
            return temp;
        }
        temp = temp->getNextSong();
        ++count;
    }
    return nullptr;
}
void Playlist::displayLoadedSongs(bool displayNumbers) const{
    if(firstSong == nullptr){
        cout << "No songs are currently loaded for play." <<endl;
    }
    Song *temp = firstSong;
    int numDisp = 0;
    while(temp){
        if(displayNumbers){
            cout << numDisp + 1 << ". ";
            if(numDisp+1 < 10){
                cout << "  ";
            }
            else if(numDisp+1 < 100){
                cout << " ";
            }
        }
        cout  << temp->getTitle() << endl;
        temp = temp->getNextSong();
        numDisp+=1;
    }
}
Playlist& Playlist::operator=(const Playlist& rhs){
    numberSongsLoaded = rhs.numberSongsLoaded;
    name = rhs.name;
    if(rhs.firstSong == nullptr){
        firstSong = lastSong = nullptr;
    }
    else{
    Song* temp = rhs.firstSong;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
    }
    return *this;
}
void Playlist::operator+(Song newSong){
    addNewSong(newSong);
}
void Playlist::addNewSong(const Song& newSong){
    if(checkIfSongIsInPlaylist(newSong)){
        return;
    }

    Song* temp = new Song;
    
    temp->setTitle(newSong.getTitle());
    temp->setArtist(newSong.getArtist());
    temp->setNextSong(nullptr);
    if(firstSong == nullptr){
        firstSong = lastSong = temp;
        ++numberSongsLoaded;
    }
    else{
        lastSong->setNextSong(temp);
        lastSong = temp;
        ++numberSongsLoaded;
    }
    
}
void Playlist::operator-(int songInd){
    deleteSong(songInd);
}
bool Playlist::check(const Song& newSong){
    return checkIfSongIsInPlaylist(newSong);
}
void Playlist::displaySongsWithoutNum(){
    Song* temp = firstSong;
    while(temp != nullptr){
        cout << *temp;
        temp = temp->getNextSong();
    }
}

