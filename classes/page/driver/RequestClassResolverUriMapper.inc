<?php


namespace page\driver;


/**
 * The RequestClassResolverUriMapper class is responsible for mapping request URIs to corresponding class names.
 * It provides a centralized mechanism for managing URI-to-class mappings, simplifying maintenance and scalability.
 * By encapsulating the mapping logic, it enhances the modularity and testability of the application.
 *
 * @deprecated 
 */
class RequestClassResolverUriMapper
{


	/**
	 * An associative array mapping URI patterns to class names.
	 * Keys are regular expressions representing the URI patterns, and values are the fully qualified class names to instantiate.
	 * This structure allows for flexible and dynamic URI pattern matching, facilitating the addition or modification of routes.
	 */
	private static array $_uriClassMap = [
		"/\/project\/list\/?/i" => "\page\ProjectList",
		"/\/project\/state\/list\/?/i" => "\page\ProjectStateList",
		"/\/project\/(\d+)\/detail\/?/i" => "\page\ProjectDetail",
		"/\/client\/list\/?/i" => "\page\ClientList",
		// Additional mappings can be added here.
	];


	/**
	 * The default class to instantiate if no matching pattern is found in the URI mapping.
	 * This provides a fallback mechanism, ensuring that the application can still provide a response even when no specific route matches.
	 */
	private static string $_defaultClass = "\page\Home";


	/**
	 * Retrieves class information and matching results based on the provided URI.
	 * This method iterates over the URI mapping definitions, applying regular expression matching to find a corresponding class.
	 *
	 * @param string $uri The request URI to resolve to a class name.
	 *
	 * @return array An associative array containing the class name ('className') and any matches ('matches') from the regex pattern.
	 */
	public static function _getClassInfo(string $uri): array
	{
		foreach (self::$_uriClassMap as $pattern => $className) {
			if (preg_match($pattern, $uri, $matches)) {
				return [
					"className" => $className,
					"matches" => $matches,
				];
			}
		}

		// Returns the default class and an empty matches array if no mapping is found.
		return [
			"className" => self::$_defaultClass,
			"matches" => [],
		];
	}


}
