# for making the man-page out of the asciidoc-file:
man:
	a2x -f manpage documentation.asciidoc

# following generates a HTML-file (readable with a browser) out of the asciidoc-file:
html:
	a2x -f xhtml documentation.asciidoc

# cleaning the directory; deletes all files except the asciidoc-code and this makefile:
clean:
	find -not -name "." -and -not -name "makefile" -and -not -name "documentation.asciidoc" -exec rm {} \;