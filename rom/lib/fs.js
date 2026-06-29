function OpenFile_Handle(fs_handle) {
    var fileObject = {
        handle: fs_handle,
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
            var next_handle = FS.OpenNextFile(this.handle);
            if (next_handle == null)
                return null;
            return OpenFile_Handle(next_handle);
        },
        IsDir: function () {
            return FS.IsDirectoryFilePointer(this.handle);
        }
        ,
        Rewind: function () {
            FS.Rewind(this.handle);
        }
        ,
        SeekDir: function (pos) {
            return FS.SeekDir(this.handle, pos);
        }
        ,
        Seek: function (pos) {
            return FS.Seek(this.handle, pos);
        }
    };
    return fileObject;
}
function OpenFile(filename, mode) {
    return OpenFile_Handle(FS.Open(filename, mode));
}