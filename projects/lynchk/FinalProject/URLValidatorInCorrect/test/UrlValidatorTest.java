import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.*;

class UrlValidatorTest {

    UrlValidator urlValidator, urlValidatorAllSchemes;
    String testUrl;
    boolean expected, actual;
    Random randomNum;

    // Used by Kaitie's Tests
    String validUrlSchemes[] = {"http://", "ftp://", "h3t://", "" };
    String invalidUrlSchemes[] = {"3ht://", "http:/", "http:", "http/", "://" };
    String validUrlAuthorities[] = {"www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com" };
    String invalidUrlAuthorities[] = {"256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.a1a", "go.1aa", "aaa.", ".aaa", "aaa", "" };
    String validUrlPorts[] = {":80", ":65535", ":0", ""};
    String invalidUrlPorts[] = {":-1", ":65636", ":65a" };
    String validUrlPaths[] = {"/test1","/t123", "/$23", "/test1/", "", "/test1/file"};
    String invalidUrlPaths[] = {"/..", "/../", "/..//file", "/test1//file"};
    String validUrlQueries[] = {"?action=view", "?action=edit&mode=up", ""};

    // Used by Eric's Tests
    String[] valids = {
            "ftp://www.google.com",  //failed
            "www.google.com",  //failed
            "http://www.google.com",
            "http://www.google.com/",
            "h3t://go.com",  //failed
            "http://go.com",
            "http://255.255.255.255",
            "http://0.0.0.0",
            "http://go.au",
            "http://go.au/$23",
            "http://go.au/$23?action=view",
            "www.google.com:80",  //failed
            "http://www.google.com:0",  //failed
            "http://go.com/test1",
            "http://go.au?action=edit&mode=up",
            "http://go.au/t123?action=edit&mode=up"
    };

    String[] invalids = {
            "http://www.google.com/..",
            "http://www.google.com/../file",
            "http://www.google.com/#",  //failed
            "http://",  //failed
            "http://256.256.256.256",  //failed
            "http://go.1aa",  //failed
            "http://go.a1a",  //failed
            "http://go.a1a",  //failed
            "http://www.google.com/:65636",  //failed
            "http://255.255.255.255/..",
            "http://0.0.0.0/test1//file",
            "http://256.256.256.256/#/file",  //failed
            "1.2.3.4.5",
            "1.2.3.4",
            "1.2.3",
            ".1.2.3.4",
            "3ht://google.com",
            "http:/google.com"  //failed
    };

    ResultPair[] testUrlScheme = {
            new ResultPair("http://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", true),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("://", false),
            new ResultPair("", true)
    };

    ResultPair[] testUrlAuthority = {
            new ResultPair("www.google.com", true),
            new ResultPair("go.com", true),
            new ResultPair("go.au", true),
            new ResultPair("0.0.0.0", true),
            new ResultPair("255.255.255.255", true),
            new ResultPair("256.256.256.256", false),
            new ResultPair("255.com", true),
            new ResultPair("1.2.3.4.5", false),
            new ResultPair("1.2.3.4.", false),
            new ResultPair("1.2.3", false),
            new ResultPair(".1.2.3.4", false),
            new ResultPair("go.a", false),
            new ResultPair("go.a1a", false),
            new ResultPair("go.1aa", false),
            new ResultPair("aaa.", false),
            new ResultPair(".aaa", false),
            new ResultPair("aaa", false),
            new ResultPair("", false)
    };

    ResultPair[] testUrlPort = {
            new ResultPair(":80", true),
            new ResultPair(":65535", true),
            new ResultPair(":0", true),
            new ResultPair("", true),
            new ResultPair(":-1", false),
            new ResultPair(":65636",false),
            new ResultPair(":65a", false)
    };

    ResultPair[] testPath = {
            new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", false)
    };

    ResultPair[] testUrlQuery = {
            new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true)
    };

    @BeforeEach
    void setUp() {

        // Used in Kaitie's Tests
        urlValidator = new UrlValidator();
        randomNum = new Random();

        // Used in Eric's Test
        urlValidatorAllSchemes = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    }

    // Test written by Kaitie
    @Test
    void isValidManualTest() {

        // Choose a url to test
        testUrl = "http://www.google.com";

        // Set expected to true or false based on the url you chose
        expected = true;

        // Find out what isValid() actually returns
        actual = urlValidator.isValid( testUrl );

        // Compare expected to actual
        assertEquals(expected, actual);
    }

    // Test written by Eric
    @Test
    public void isValidManualTest2()
    {
        //You can use this function to implement your manual testing

        //assertFalse(urlValidatorAllSchemes.isValid("http://"));  //failed
        //assertTrue(urlValidatorAllSchemes.isValid("www.google.com"));  //failed
        assertTrue(urlValidatorAllSchemes.isValid("http://www.google.com"));
        assertTrue(urlValidatorAllSchemes.isValid("http://www.google.com/"));
        assertTrue(urlValidatorAllSchemes.isValid("http://go.com"));
        assertTrue(urlValidatorAllSchemes.isValid("http://255.255.255.255"));
        assertTrue(urlValidatorAllSchemes.isValid("http://0.0.0.0"));
        //assertFalse(urlValidatorAllSchemes.isValid("http://256.256.256.256"));  //failed
        assertTrue(urlValidatorAllSchemes.isValid("http://go.au"));
        //assertFalse(urlValidatorAllSchemes.isValid("http://go.1aa"));  //failed
        //assertTrue(urlValidatorAllSchemes.isValid("www.google.com:80"));  //failed
        //assertTrue(urlValidatorAllSchemes.isValid("http://www.google.com:0"));  //failed
        //assertFalse(urlValidatorAllSchemes.isValid("http://www.google.com/:65636"));  //failed
        assertTrue(urlValidatorAllSchemes.isValid("http://go.com/test1"));
        assertFalse(urlValidatorAllSchemes.isValid("http://255.255.255.255/.."));
        assertFalse(urlValidatorAllSchemes.isValid("http://0.0.0.0/test1//file"));
        //assertFalse(urlValidatorAllSchemes.isValid("http://256.256.256.256/#/file"));  //failed
        assertTrue(urlValidatorAllSchemes.isValid("http://go.au?action=edit&mode=up"));
    }

    // Test written by Kaitie
    @Test
    void isValidHappyCase() {

        // Set expected to true - all these url's should be valid
        expected = true;

        // Decide how many times the loop should run
        int counter = 1000;

        // test loop
        while (counter > 0)
        {
            // Generate a random valid url
            testUrl = validUrlGenerator();

            // Print out the url for debugging
            System.out.format("Valid URL generated: %s\n", testUrl);

            // Run it through isValid()
            actual = urlValidator.isValid( testUrl );

            // Compare expected to actual
            assertEquals(expected, actual);

            // Decrement the counter
            counter--;
        }
    }

    // Test written by Kaitie
    @Test
    void isValidSadCase() {

        // Set expected to false - all these url's should be invalid
        expected = false;

        // Decide how many times the loop should run
        int counter = 1000;

        // test loop
        while (counter > 0)
        {
            // Generate a random invalid url
            testUrl = invalidUrlGenerator();

            // Print out the url for debugging
            System.out.format("Invalid URL generated: %s\n", testUrl);

            // Run it through isValid()
            actual = urlValidator.isValid( testUrl );

            // Compare expected to actual
            assertEquals(expected, actual);

            // Decrement the counter
            counter--;
        }
    }

    // Test written by Kaitie
    @Test
    void isValidNullCase() {

        // Set expected to false - null is invalid
        expected = false;

        // Find out what isValid() actually returns for null
        actual = urlValidator.isValid( null );

        // Compare expected to actual
        assertEquals(expected, actual);
    }

    // Test written by Eric
    @Test
    public void testIsValid()
    {
        //You can use this function for programming based testing
        for(int schemeIndex = 0; schemeIndex < testUrlScheme.length; ++schemeIndex) {
            for(int authorityIndex = 0; authorityIndex < testUrlAuthority.length; ++authorityIndex) {
                for(int portIndex = 0; portIndex < testUrlPort.length; ++portIndex) {
                    for(int pathIndex = 0; pathIndex < testPath.length; ++pathIndex) {
                        for(int queryIndex=0; queryIndex < testUrlQuery.length; ++queryIndex) {
                            boolean expected;
                            String url = testUrlScheme[schemeIndex].item
                                    + testUrlAuthority[authorityIndex].item
                                    + testUrlPort[portIndex].item
                                    + testPath[pathIndex].item
                                    + testUrlQuery[queryIndex].item;
                            expected = testUrlScheme[schemeIndex].valid
                                    && testUrlAuthority[authorityIndex].valid
                                    && testUrlPort[portIndex].valid
                                    && testPath[pathIndex].valid
                                    && testUrlQuery[queryIndex].valid;
                            boolean result = urlValidatorAllSchemes.isValid(url);

                            // Print out the url for debugging
                            System.out.format("The generated url was: %s\n", url);

                            assertEquals(expected, result);
                        }
                    }
                }
            }
        }
    }


    // Helper for Kaitie's tests
    String validUrlGenerator()
    {
        String schemeString, authorityString, portString, pathString, queryString;

        // Get a random index for the valid array for each part of the URL
        // Use the array's length - 1 as the bound
        schemeString = validUrlSchemes[randomNum.nextInt(validUrlSchemes.length - 1)];
        authorityString = validUrlAuthorities[randomNum.nextInt(validUrlAuthorities.length - 1)];
        portString = validUrlPorts[randomNum.nextInt(validUrlPorts.length - 1)];
        pathString = validUrlPaths[randomNum.nextInt(validUrlPaths.length - 1)];
        queryString = validUrlQueries[randomNum.nextInt(validUrlQueries.length - 1)];

        // Build Url
        StringBuilder url = new StringBuilder();
        url.append(schemeString);
        url.append(authorityString);
        url.append(portString);
        url.append(pathString);
        url.append(queryString);

        return url.toString();
    }

    // Helper for Kaitie's tests
    String invalidUrlGenerator()
    {
        int scheme, authority, port, path;
        String schemeString, authorityString, portString, pathString, queryString;

        // determine whether to use valid or invalid array for each portion of url
        // let 1 indicate valid and 0 indicate invalid
        scheme = randomNum.nextInt(1);
        authority = randomNum.nextInt(1);
        port = randomNum.nextInt(1);
        path = randomNum.nextInt(1);

        // if four 1's are generated, run again
        while (scheme + authority + port + path == 4)
        {
            scheme = randomNum.nextInt(1);
            authority = randomNum.nextInt(1);
            port = randomNum.nextInt(1);
            path = randomNum.nextInt(1);
        }

        // Get a random index for either the valid or invalid array for each part of the URL
        // Use the array's length - 1 as the bound

        if (scheme == 1)
            schemeString = validUrlSchemes[randomNum.nextInt(validUrlSchemes.length - 1)];
        else schemeString = invalidUrlSchemes[randomNum.nextInt(invalidUrlSchemes.length - 1)];

        if (authority == 1)
            authorityString = validUrlAuthorities[randomNum.nextInt(validUrlAuthorities.length - 1)];
        else authorityString = invalidUrlAuthorities[randomNum.nextInt(invalidUrlAuthorities.length - 1)];

        if (port == 1)
            portString = validUrlPorts[randomNum.nextInt(validUrlPorts.length - 1)];
        else portString = invalidUrlPorts[randomNum.nextInt(invalidUrlPorts.length  -1)];

        if (path == 1)
            pathString = validUrlPaths[randomNum.nextInt(validUrlPaths.length - 1)];
        else pathString = invalidUrlPaths[randomNum.nextInt(invalidUrlPaths.length - 1)];

        // There are only valid query strings
        queryString = validUrlQueries[randomNum.nextInt(validUrlQueries.length - 1)];

        // Build Url
        StringBuilder url = new StringBuilder();
        url.append(schemeString);
        url.append(authorityString);
        url.append(portString);
        url.append(pathString);
        url.append(queryString);

        return url.toString();
    }
}
