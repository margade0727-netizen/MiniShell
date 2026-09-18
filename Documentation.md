Documentation
    Functions
        Whereami() - Call [Whereami] - Returns current location of the user in string.
            Whereami
        Whoami() - Call [Whoami] - Returns current user in string.
            Whoami
        List() - Call [List || ls] - Lists the all available files, along with file types in the current folder
            List
            ls
        Create() - Call [Create || crt ] - Creates an empty text file in the current folder.
            Create [file name]
            crt [file name]
        Rename() - Call [Rename] - Renames the chosen file by another name.
            Rename [file name] [filename2]
        Delete() - Call [Delete || rm || Del] - Deletes/Removes chosen file.
            Delete [filename]
            rm [filename]
            Del [filename]
        DeleteDirective - Call [DeleteDirective || rmdir || Deldir] - Deletes/Removes chosen folder.
            Deldir [foldername] [-f (force)]
        Move() - Call [move || mv] - Moves chosen file/folder
            move [path] [path2]
        Open() - Call [open || op ] - Opens file in readable form. //can only open readable files//
            open [path/filename]
            op [path/filename]
    
Non-user Dependent Functions /NDFs/ -- List of functions that are done by the CLI that isn't directly dependent on user (i.e isn't required to called-out to work)
        command-check() --checks commands for validity. 
        input-check() -- checks input for validity.
        suggestion() -- suggests when user writes input.
        

