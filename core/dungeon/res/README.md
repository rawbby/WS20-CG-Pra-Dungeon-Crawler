# Resource Readme

use the following command to compress resource folders

```
cd <res_directory>
cmake -E tar cz <file_name>.tar.gz -- <relative_path>
```

where <res_directory> is this parent working directory
where <file_name> is the name of the resource folder
where <relative_path> the relative path to folder from this parent working directory

__Example:__

```
cmake -E tar cz materials/gametextures.tar.gz -- materials/gametextures
```
