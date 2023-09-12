`static`
## Static content for GitHub Pages
Content (e.g. images, PDFs, HTML) in GitHub Pages repositories consume 3x storage
- original
- copied into: ./_site/
- also in: .git/objects/pack/

Moving static content to a separate GitHub repository could reduce:
- storage overhead
- GitHub Pages build time  
- provided that an appropriate GitHub action replaces Jekyll

### Status
- Deployed as [`/static/` folder](https://blekenbleu.github.io/static/)
 to [GitHub Pages](https://blekenbleu.github.io/):  
    ![settings](static.gif)  
- Trivial `Gemfile` and `_config.yml` were added to keep default GitHub Action from failing  

### Content
- [altec](altec/index.htm)
- [AT-LP140XP](AT-LP140XP/index.htm)
- [Canon](Canon/index.html)
- [Carver](Carver/index.htm)
- [ColorRendering](ColorRendering/index.html)
- [covid](covid/index.htm)
- [ESP32](ESP32/index.htm)
- [GitHubW11](GitHubW11/index.htm)
- [HTML](HTML/README.md)
- [ImageProcessing](ImageProcessing/index.htm)
- [images](images/)
- [Mastodon](Mastodon/TeslaTrump/index.htm)
- [network](network/index.htm)
- [SL-7](SL-7/index.htm)
- [story](story/index.htm)
- [SimHub](SimHub/index.htm)
- [TThistory](TThistory/)
