<?php


namespace page;


/**
 * The PageFiles class manages file links for a web page. It allows the addition of files
 * with distinction between relative and absolute paths and provides a method to iterate over these files.
 * This class can be used to manage various types of files, not just CSS or JS.
 */
class PageFiles
{


	/**
	 * @var array An associative array storing the files where the key is the file path and
	 * the value is a boolean indicating whether the path is absolute (true) or relative (false).
	 */
	private array $repository = [];

	/**
	 * @var string The root directory for relative files. This path is prepended to
	 * relative file paths during iteration.
	 */
	private string $root = "";


	/**
	 * Sets the root directory for relative files. This directory is prepended to the relative file paths.
	 *
	 * @param   string  $root  The root directory for files.
	 */
	public function setRoot(string $root): void
	{
		$this->root = rtrim($root, '/').'/';
	}


	/**
	 * Adds a file to the list. If the file is already present, it updates whether it's treated as absolute or relative.
	 * Using the file path as a key ensures that each file is only included once.
	 *
	 * @param   string  $file        The path of the file to add.
	 * @param   bool    $isAbsolute  Specifies whether the path is absolute or relative. Default is false (relative).
	 */
	public function addFile(string $file, bool $isAbsolute = false): void
	{
		$this->repository[$file] = $isAbsolute;
	}


	/**
	 * Provides a generator to iterate over the files. For relative paths, the root directory is prepended.
	 * This method yields the full path of each file, considering whether it's relative or absolute.
	 *
	 * @return \Generator A generator that yields the full path of each file.
	 */
	public function filesIterator(): \Generator
	{
		foreach ($this->repository as $file => $isAbsolute) {
			yield $isAbsolute ?$file: $this->root.$file;
		}
	}


}
