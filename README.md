`static`
## Static content for GitHub Pages
Content (e.g. images, PDFs, HTML) in GitHub Pages repositories consume 3x storage
- original
- copied into: ./_site/
- also in: .git/objects/pack/

Moving static content to a separate GitHub repository may reduce:
- storage overhead
- GitHub Pages build time  
- provided that an appropriate GitHub action replaces Jekyll

### Status
- Deployed as [`/static/` folder](https://blekenbleu.github.io/static/)
 to [GitHub Pages](https://blekenbleu.github.io/):  
    ![settings](static.gif)  
- This technique is sometimes called a [GitHub Pages **project** site](https://docs.github.com/en/pages/getting-started-with-github-pages/about-github-pages#types-of-github-pages-sites).  
- Trivial `Gemfile` and `_config.yml` were added to stop *default* GitHub Action from failing  

### To Do
Consider using [`static.yml`](https://github.com/actions/starter-workflows/blob/main/pages/static.yml)
 as a [Custom Action](https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site)  
**Alternatively**, <a href="https://poldham.github.io/simple_website/publishing.html">a `.nojekyll` file in the root directory</a> (along with `README.md` and `index.html`),  
but all other static content already in `_site` folder (which would be removed from `.gitignore`).  

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
