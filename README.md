# Recently-Deleted
The program is designed to recover JPEG images from a raw memory card file (like card.raw). It scans through the file, identifies the beginning of each JPEG image, and writes these images into separate files.
The program reads data from a memory card file in chunks of 512 bytes.
It checks each chunk to see if it’s the start of a new JPEG.
If it finds a new JPEG, it closes the previous file (if any), creates a new one, and writes the data to it.
This continues until the entire memory card has been read, and all JPEGs have been recovered and saved as separate files.
This code essentially automates the process of extracting images from a corrupted or unorganized memory card, assuming the images are stored in a standard JPEG format.
