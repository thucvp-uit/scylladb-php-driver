use cc::Build;
use walkdir::WalkDir;

fn add_files(build: &mut Build, dir: &str) {
    let dir = WalkDir::new(dir).follow_links(false);

    dir.into_iter()
        .filter_map(|e| e.ok())
        .filter(|e| e.file_type().is_file())
        .filter(|e| e.path().extension().unwrap().to_str().unwrap() == "cpp")
        .filter(|e| e.path().extension().unwrap().to_str().unwrap() == "c")
        .for_each(|e| {
            build.file(e.path());
        });
}

fn main() {
    let mut build = Build::new();
    build
        .cpp(true)
        .include(".")
        .include("include")
        .include("util/include")
        .include("php/8.2-debug-nts/include/php")
        .include("php/8.2-debug-nts/include/php/main")
        .include("php/8.2-debug-nts/include/php/ext")
        .include("php/8.2-debug-nts/include/php/sapi")
        .include("php/8.2-debug-nts/include/php/TSRM")
        .include("php/8.2-debug-nts/include/php/Zend")
        .include("ZendCPP")
        .include("ZendCPP/String")
        .define("HAVE_DLFCN_H", Some("1"))
        .define("HAVE_STDIO_H", Some("1"))
        .define("HAVE_STDINT_H", Some("1"))
        .define("HAVE_INTTYPES_H", Some("1"))
        .define("HAVE_SYS_STAT_H", Some("1"))
        .define("HAVE_SYS_TYPES_H", Some("1"))
        .define("HAVE_STRING_H", Some("1"))
        .define("HAVE_UNISTD_H", Some("1"))
        .file("./php_driver.cpp")
        .extra_warnings(true);

    for item in &["src", "ZendCPP"] {
        add_files(&mut build, item);
    }

    build.compile("cassandra");
}
