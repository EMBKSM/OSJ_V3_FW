idf_component_register(SRCS "osj_http.c"
                       INCLUDE_DIRS "include"
                       EMBED_TXTFILES "html/index.html" "html/style.css"
                       REQUIRES esp_http_server)
