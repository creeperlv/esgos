function OpenFile(filename, mode) {
    var fileObject = {
        handle: FS.Open(filename, mode),
        Close: function () {
            FS.Close(this.handle);
        },
        GetName: function () {
            return FS.GetName(this.handle);
        },
        GetPath: function () {
            return FS.GetPath(this.handle);
        },
        ReadChar: function () {
            return FS.ReadChar(this.handle);

        },
        ReadLine: function () {
            return FS.ReadLine(this.handle);
        
        },
        OpenNextFile: function () {
            return FS.OpenNextFile(this.handle);
        }
    };

}