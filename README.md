VE is a terminal text editor for the Portfolio project using C programming langauge.


+++ indicate what will be included
--- indicate what is not included or will be included in the future
=== indicate a section of the what is being discussed

=================================================================================================================================================================================================================================================================================


Project Title: "VE: A Lightweight Text Editor built in C"

Introduction/Overview:
Brief Summary: VE is a lightweight, terminal-based text editor built using the C programming language. The project aims to create a simple, fast, and efficient text editor that supports basic text editing functionalities, making it suitable for quick editing tasks directly from the terminal. The editor is designed with performance and minimalism in mind, catering to users who prefer a command-line interface (CLI) over graphical user interfaces (GUIs).

Background: Text editors are essential tools for developers and system administrators. While there are many advanced text editors available, there is a need for a minimalist editor that is easy to use, has a small footprint, and can be quickly invoked from the command line. VE addresses this need by providing a basic yet powerful text editor that focuses on core editing functionalities without unnecessary bloat.

Objectives: A very minimal and easy to use terminal text editor .



Primary Goals:===================================================================================================================================================================================================================================================================
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Basic Text Editing: Implement core text editing features such as opening files, inserting, deleting, and saving text.

Navigation: Provide efficient navigation within the text file, including moving the cursor.

File Management: Allow users to open, edit, and save files from within the editor.

Secondary Goals:=================================================================================================================================================================================================================================================================
-------------------------------------------------------------------------------------------

Syntax Hightlighting:== Introduce basic syntax highlightinig for basic text editing.

Undo/Redo Functionality: Implement a simple undo/redo mechanism to enhance editing experience.

Cross-Platform Compatibility: Ensure that the text editor can be compiled and run on major operating systems. (Linux, macOS, Windows).

Scope: ==========================================================================================================================================================================================================================================================================

Core Features: Implement essential text editing functions, including file handling, text manipulation, and navigation.

Customization: Provide options for configuring basic settings like tab width and line numbering.

CLI Integration: Ensuring seamless operation from the command line with support for standard input/output redirection.

Basic Syntax Highlighting: Develop a system for highlighting syntax in supported languages.

Development Phase:==
Editor Core: Develop the core editing functionalities, including text manipulation, file handling, and navigation.

User Interface: Implement a basic terminal-based UI, ensuring a clean and intuitive experience.

Customization: Add options for the user customization, such as tab width and line numbering.

Testing Phase: Conduct rigorous testing, including testing, including unit tests for core functions and user acceptance testing for overall usability.

Optimization: Optimize the editor for performance, ensuring it can handle large fiels efficiently.

Documentation: Provide a more comprehensive documentation on how to use the program, including a user manual and developer guide.

Tools and Technologies: C , SDL2, SDL2_ttf(for font), make(command line tool), ncurses

Programming Language: C

Text Interface: ncurses library for terminal handling and user interface.
GUI Interface: SDL2 and SDL2_ttf

Build System: Makefile for compiling and linking of the program.

Version Control: Git for source code management.

Testing : Custom test cases and <assert.h> library for testing and assurance.

Team Roles: ==

