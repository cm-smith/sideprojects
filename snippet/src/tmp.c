
void editEntry(unsigned long hash_id, int delete);

void editEntry(unsigned long hash_id, int delete) {
	char* action;
	if (delete) {
		action = "delete";
	}
	else {
		action = "edit";
	}

	// https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--
	/* Open the file for reading */
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	int line_count = 0;
	ssize_t line_size;
	FILE *fp = fopen(OUTPUT_FILE, "r");

	if (!fp) {
		fprintf(stderr, "Error opening file '%s'\n", OUTPUT_FILE);
		return;
	}

	/* Get the first line of the file. */
	line_size = getline(&line_buf, &line_buf_size, fp);

	// Track if we made the edit
	int edit_complete = 0;

	/* Loop through until we are done with the file. */
	while ((line_size >= 0) && (edit_complete == 0)) {
		// http://www.cplusplus.com/reference/cstring/strtok/
		char *ptr;

		// https://stackoverflow.com/a/6389959
		if (hash_id == strtoul(line_buf, &ptr, 10)) {
			// Print entry that matches hash key
			printf("\nFound entry: %s", ptr);

			// Request user confirmation (hash collisions may exist)
			printf("Is this the entry you would like to %s? (y/n) ", action);
			char* response = inputString(stdin,10);

			if (tolower(response[0])=='y') {
				if (delete == 1) {
					// Delete line in file
				}
				else {
					// Initialize edits
					char *edit_project = NULL;
					char *edit_accomplish = NULL;

					// Grab date from previous line (this will remain)
					char *old_date = strtok(line_buf,"()");
					old_date = strtok(NULL,"()");

					// Grab edits for project title
					printf("Re-enter the project name (default will set this to '%s'): ", DEFAULT_PROJECT);
    					edit_project = inputString(stdin, 10);

					// Grab edits for accomplishment
					printf("Re-enter the accomplishment: ");
    					edit_accomplish = inputString(stdin, 10);

					// Print output to user
					printf("%lu (%s) %s: %s\n", hash_id, old_date, edit_project, edit_accomplish);

					// Break out the loop
					edit_complete = 1;

					SAFEFREE(edit_project);
					SAFEFREE(edit_accomplish);
				}
			}

			SAFEFREE(response);
		}

		/* Get the next line */
		line_size = getline(&line_buf, &line_buf_size, fp);
	}

	/* Free the allocated line buffer */
	SAFEFREE(line_buf);

	/* Close the file now that we are done with it */
	fclose(fp);
}
