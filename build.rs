use std::fs::read_dir;

use cc::Build;

fn main() {
    let mut build = Build::new();

    build
        .cpp(true)
        .include("include")
        .include("util/include")
        .include("ZendCPP")
        .include("ZendCPP/String")
        .include(".")
        .define("HAVE_DLFCN_H", Some("1"))
        .define("HAVE_STDIO_H", Some("1"))
        .define("HAVE_STDINT_H", Some("1"))
        .define("HAVE_INTTYPES_H", Some("1"))
        .define("HAVE_SYS_STAT_H", Some("1"))
        .define("HAVE_SYS_TYPES_H", Some("1"))
        .define("HAVE_STRING_H", Some("1"))
        .define("HAVE_UNISTD_H", Some("1"))
        .extra_warnings(true);

    read_dir("src").unwrap().for_each(|entry| {
        let entry = entry.unwrap();
        let path = entry.path();

        println!("{:?}", path);
        let ext = path.extension().unwrap().to_str();

        if ext == Some("cpp") || ext == Some("c") {
            build.file(path);
        }
    });

    read_dir("util/src").unwrap().for_each(|entry| {
        let entry = entry.unwrap();
        let path = entry.path();

        let ext = path.extension().unwrap().to_str();

        if ext == Some("cpp") || ext == Some("c") {
            build.file(path);
        }
    });

    read_dir("ZendCPP/String").unwrap().for_each(|entry| {
        let entry = entry.unwrap();
        let path = entry.path();

        let ext = path.extension().unwrap().to_str();

        if ext == Some("cpp") || ext == Some("c") {
            build.file(path);
        }
    });

    read_dir("ZendCPP").unwrap().for_each(|entry| {
        let entry = entry.unwrap();
        let path = entry.path();

        let ext = path.extension().unwrap().to_str();

        if ext == Some("cpp") || ext == Some("c") {
            build.file(path);
        }
    });

    build.compile("cassandra");
}
