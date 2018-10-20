# Cookiecutter template for C++ projects

Generate a new C++ project with a quick cookiecutter command:

```
$ cookiecutter cookiecutter-cpp-project
```

## Features

- Generates a new C++ project built with CMake
- It can optionally include installation commands
- It can optionally generate configuration for building `DEB` and `RPM` packages with CPack
- It generates a `man` page
- It can optionally add CMake configuration for Boost, SFML, GoogleTest

## Variables

| Variable       | Description         |
|----------------|---------------------|
| `project_name` | Name of the project |
| `project_short_description` | Short description of the project |
| `license` | License e.g. `GPLv3` |
| `author_name` | Author's name |
| `author_email` | Author's email |
| `cpp_standard` | C language standard, e.g. `17`, `11` |
| `add_installation` | If `y` then installation command (`make install`) will be generated |
| `use_cpack` | If `y` then commands to generate `DEB` and `RPM` packages will be added |
| `add_boost` | If `y` then it will be built with Boost library |
| `add_sfml` | If `y` then it will be built with SFML library |
| `add_google_test` | If `y` then it will add support for tests with GoogleTest |
