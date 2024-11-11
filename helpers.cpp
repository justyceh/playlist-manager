// Justyce Hickman, PA2, 11/10/24
#include "helpers.h"

void promptSongSelection(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded() +1 << ". Exit Program" <<endl;
    cout << "Please enter the number of the song to be added to your playlist: ";
}
void promptSongSelectionNew(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded() +1 << ". Finalize List" <<endl;
    cout << allSongs.getNumSongsLoaded() +2 << ". Exit Program" <<endl;
}
void promptSongSelectionAddSong(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded() +1 << ". Return to Playlist Options Menu." <<endl;
    cout << allSongs.getNumSongsLoaded() +2 << ". Exit Program" <<endl;
}
void promptSongSelectionLoadPlaylist(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded() + 1 << ". Return to Main Menu" << endl;
    cout << allSongs.getNumSongsLoaded() + 2 << ". Exit Program." << endl;
}


void readData(ifstream& inFile, Playlist& allSongs){
    string temp;
    int numSongsTotal = 0;
    while(!inFile.eof()){
        Song newSong;
        getline(inFile, temp, '-');
        newSong.setTitle(temp);
        getline(inFile, temp);
        newSong.setArtist(temp);
        allSongs + newSong;
        ++numSongsTotal;
    }
    
}

void displayMainMenu(){
    cout <<endl<< "Welcome to SongStoreSupreme!" <<endl;
    cout << "1. Load an existing playlist."<<endl;
    cout << "2. Create a new playlist." <<endl;
    cout << "3. Exit SongStoreSupreme." <<endl;
}

bool createNewPlaylist(const Playlist& allSongs, Playlist& newPlaylist){

    string pName;

    do{
        cout << "Playlist name: ";
        cin >> pName;
        if(playlistExists(pName)){
            cout << "Another playlist already exists with that name." << endl << endl;
     }
    }while(playlistExists(pName));
    newPlaylist.setName(pName);




    cout << "Displaying Available Songs:" << endl;
    promptSongSelectionNew(allSongs);
    int finalizeInput = allSongs.getNumSongsLoaded() + 1;
    int quitInput = allSongs.getNumSongsLoaded() + 2;
    int input;
    do{
        if(newPlaylist.getNumSongsLoaded() == allSongs.getNumSongsLoaded()){
            char choice;
            do{
                cout << "Would you like to save (y/n): ";
                cin >> choice;
            }while(choice != 'y' && choice != 'n');
            if(choice == 'y'){
                writePlaylistToFile(newPlaylist);
                return true;
            }
            else{
                return true;
            }
        }
      cout << "Make a selection: ";
      cin >> input;
      if(input == finalizeInput){
        if(newPlaylist.getNumSongsLoaded() > 0){
            writePlaylistToFile(newPlaylist);
            }
        return false;
      }
      else if(input == quitInput || input > quitInput){
        if(newPlaylist.getNumSongsLoaded() > 0){
            char choice;
            do{
                cout << "Would you like to save (y/n): ";
                cin >> choice;
            }while(choice != 'y' && choice != 'n');
            if(choice == 'y'){
                writePlaylistToFile(newPlaylist);
                return true;
            }
            else{
                return true;
            }
        }
        return true;
      }
      else{
        newPlaylist + *allSongs.getSongAtIndex(input);
      }
    }while(input <= allSongs.getNumSongsLoaded() && input > 0);
return true;
}

void writePlaylistToFile(Playlist& playlist){
    ofstream file(playlist.getName() + ".txt");
    Song* temp = playlist.getFirstSong();
    int numSongs = playlist.getNumSongsLoaded();
    int count = 0;
    while(temp != nullptr){
        if(temp->getNextSong() == nullptr){
            file << temp->getTitle() << "-" << temp->getArtist();
            break;
        }
        else{
        file << temp->getTitle() << "-" << temp->getArtist() <<  '\n';
        temp = temp->getNextSong();
        }
    }
        file.close();
    
}
bool playlistExists(string newPlaylist){

    string playlist[100];
    int n = getExistingPlaylists(playlist);
    for(int i = 0; i < n; i++){
        if(playlist[i] == newPlaylist){
            return true;
        }
    }
    return false;
}
void promptPlaylistSelection(string* existingPlaylists, int numPlaylists){
    cout << endl;
    cout << "The following playlists are currently available:" <<endl;
    for(int i =0; i< numPlaylists; i++){
        cout << i+1 << ". " << existingPlaylists[i] << endl;
    }
    cout << numPlaylists + 1 << ". Return to Main Menu." << endl;
    cout << numPlaylists +2  << ". Exit Program." << endl << endl;
}

void promptModificationsToExistingPlaylist(){
    cout << "1. Modify Playlist." <<endl;
    cout << "2. Delete Playlist." << endl;
    cout << "3. Return to Main Menu." <<endl;
    cout << "4. Exit Program." <<endl;
}

void promptTypesModificationSelection(){
    cout << "1. Remove Song(s)." <<endl;
    cout << "2. Add Song(s)." <<endl;
    cout << "3. Return to Playlist Options Menu." <<endl;
    cout << "4. Exit." <<endl;
}

bool deleteSongFromPlaylist(Playlist& playlist){
    int input;
    int songsToDelete[100];
    int numSongsDeleted = 0;
    int n = playlist.getNumSongsLoaded();

    cout << "========" << playlist.getName() << "========" << endl;
    playlist.displayLoadedSongs(true);
    cout << n + 1 << ".   Return to Playlist Options Menu." << endl;
    cout << n + 2 << ".   Exit Program." << endl;


    do{
        if(numSongsDeleted == n){
            for(int i = 0; i < numSongsDeleted; i++){
                playlist - 1;
            }
            cout << "All songs deleted. Removing playlist." << endl;
            deletePlaylist2(playlist);
            cout << "Return to main menu (y/n)? ";
            char choice;
            cin >> choice;
            if(choice == 'n'){
                return true;
            }
            else{
                return false;
            }
        }
        cout << "Select a song: ";
        cin >> input;
        if(input == n+2){

            for(int i = 0; i < numSongsDeleted; i++){
                for(int j = 0; j < numSongsDeleted - i - 1; j++){
                    if(songsToDelete[j] < songsToDelete[j+1]){
                        int num = songsToDelete[j];
                        songsToDelete[j] = songsToDelete[j+1];
                        songsToDelete[j+1] = num;
                    }
                }
            }



            for(int i = 0; i < numSongsDeleted; i++){
                playlist - songsToDelete[i];
            }
            return true;
        }
        else if(input == n+1){
            if(numSongsDeleted > 0){
                 for(int i = 0; i < numSongsDeleted; i++){
                    for(int j = 0; j < numSongsDeleted - i - 1; j++){
                        if(songsToDelete[j] < songsToDelete[j+1]){
                            int num = songsToDelete[j];
                            songsToDelete[j] = songsToDelete[j+1];
                            songsToDelete[j+1] = num;
                        }
                    }
                }

                for(int i = 0; i < numSongsDeleted; i++){
                playlist - songsToDelete[i];
            }
            return false;
            }
            else{
            return false;
            }
        }
        else if(input > n + 2 || input == 0){
            continue;
            // Do nothing
        }
        else{
            songsToDelete[numSongsDeleted] = input;
            ++numSongsDeleted;
        }
    }while(input != n+1 && input != n+2);
return false;
    //if only some songs were deleted, once exiting this function, write updated playlist to file
}

bool addSongToPlaylist(Playlist& playlist, const Playlist& all){
    int input;
    char choice;
    int finalizeInput = all.getNumSongsLoaded() + 1;
    int quitInput = all.getNumSongsLoaded() + 2;
    

    do{

        promptSongSelectionAddSong(all);
        cout << "Select a song to add: ";
        cin >> input;

        if(input == finalizeInput){
            return false;
        }
        else if(input == quitInput){
            return true;
        }

    do{
        cout << "Add song to end of playlist(y/n)? ";
        cin >> choice;
    }while(choice != 'y' && choice != 'n');


    if(choice == 'y'){
        Song* temp = all.getSongAtIndex(input);
        if(!playlist.check(*temp)){
            playlist + *all.getSongAtIndex(input);
        }
        else{
            continue;
        }
    }
    else{
        cout << "========" << playlist.getName() << "========" << endl;
        int insertInput = 0;
        cout << playlist;
        cout << "Which song would you like to insert before? ";
        cin >> insertInput;
        if(playlist.check(*all.getSongAtIndex(input))){
            continue;
        }
        else{
            playlist.addNewSong(*all.getSongAtIndex(input), insertInput);
        }
    }
    }while(input <= all.getNumSongsLoaded() && input > 0);
    return false;
}

bool modifyPlaylist(Playlist& playlist, const Playlist& all){
    promptTypesModificationSelection();
    bool exit;
    int userModType, songChoice;
    do{
        cout << "What would you like to do? ";
        cin >> userModType;
    }while(userModType< 1 || userModType > 4);
    system("clear");
    switch(userModType){
        case 1:
             exit = deleteSongFromPlaylist(playlist);
            break;
        case 2:
            exit = addSongToPlaylist(playlist, all);
            break;
        case 3:
            exit = false;
            break;
        case 4: 
            exit = true;
            break;
    }
    if(playlist.getFirstSong() != nullptr){
        writePlaylistToFile(playlist); 
    }
    return exit;
}
bool deletePlaylist2(Playlist& playlist){
    while(playlist.getFirstSong() != nullptr){
            playlist.deleteSong(1);
        }
        playlist.setFirstSong(nullptr);
        playlist.setLastSong(nullptr);
        string file = playlist.getName() + ".txt";
        remove(file.c_str());
        return true;
}
bool deletePlaylist(Playlist& playlist){
        system("clear");
        cout << "========" << playlist.getName() << "========" << endl;
        playlist.displaySongsWithoutNum();
        cout << endl;

        while(playlist.getFirstSong() != nullptr){
            playlist.deleteSong(1);
        }
        playlist.setFirstSong(nullptr);
        playlist.setLastSong(nullptr);
        string file = playlist.getName() + ".txt";
        remove(file.c_str());
        cout << playlist.getName() << " deleted!" << endl;
        cout << "1. Return to Main Menu." << endl;
        cout << "2. Exit Program." << endl;
        cout << "What would you like to do?";
        return true;
}

bool manageExistingPlaylists(const Playlist& all, Playlist& selectedPlaylist){
        string names[100];
        bool exit;
        int input = 0;
        int n = getExistingPlaylists(names);
        promptPlaylistSelection(names, n);

        do{
            cout << "Which playlist would you like to load? ";
            cin >> input;
            if(input == n+2){
                return true;
            }
            else if(input == n+1){
                return false;
            }
            cout << endl;
        }while(input < 0 || input > n+2);

        ifstream file(names[input-1] + ".txt");
        readData(file, selectedPlaylist);
        file.close();
        selectedPlaylist.setName(names[input-1]);
    
        do{

            system("clear");
            cout << "========" << selectedPlaylist.getName() << "========" << endl;
            selectedPlaylist.displaySongsWithoutNum();
            cout << endl;
            promptModificationsToExistingPlaylist();
            cout << "What would you like to do with " << selectedPlaylist.getName() << "? ";
            cin >> input;

        if(input == 1){

                system("clear");
                cout << "========" << selectedPlaylist.getName() << "========" << endl;
                selectedPlaylist.displaySongsWithoutNum();
                cout << endl;
                exit = modifyPlaylist(selectedPlaylist, all);
                if(playlistExists(selectedPlaylist.getName())){

                }
                else{
                    return false;
                }
            }
        else if(input == 2){
            deletePlaylist(selectedPlaylist);
            int input;
            cin >> input;
            if(input == 2){
                return true;
            }
            else{
                return false;
            }
        }
        else if(input == 3){
            return false;
        }
        else if(input == 4){
            return true;
        }
        }while(!exit);
        return exit;
}


int getExistingPlaylists(string* existingPlaylists){
    DIR *directoryPtr = opendir(".");
    struct dirent *directoryEntry;
    int numPlaylists = 0;
    if (directoryPtr) {
        while ((directoryEntry = readdir(directoryPtr)) != NULL) {
            string filename = directoryEntry->d_name;
            string empty = "";
            if(filename != "dbSmall.txt" && filename != "dbLarge.txt"){
                for(int i = filename.size()/sizeof('c')-4; i< filename.size()/sizeof('c'); i++){
                    empty += filename[i];
                }
                if(empty == ".txt"){
                    string cleanedFilename = "";
                    for(int i = 0; i< filename.size()/sizeof('a') -4; i++){
                        cleanedFilename += filename[i];
                    }
                    existingPlaylists[numPlaylists] = cleanedFilename;
                    numPlaylists++;
                }
            }
        }
            
    closedir(directoryPtr); //close all directory
    }
    return numPlaylists;
}


ostream & operator << (ostream &out, const Song &s){
    out << s.getTitle() << endl;
    return out;
}

ostream& operator << (ostream &out, const Playlist &p){
    Song* temp = p.firstSong;
    int count = 1;
    while(temp != nullptr){
        out << count << ". " << *temp;
        ++count;
        temp = temp->getNextSong();
        
    }
    return out;
}
void getUserEntry(int& num){
    cin >> num;
}
