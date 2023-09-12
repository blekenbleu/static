`static`
## Static content for GitHub Pages
Static content (e.g. images, PDFs, HTML) in GitHub Pages repositories consume 4x storage
- original
- copied into: ./_site/
- both in: .git/objects/pack/

Moving such content to a separate GitHub repository reduces:
- storage overhead
- GitHub Pages build time
... deployed as `static` folder to [GitHub Pages](https://blekenbleu.github.io/):  
    ![settings](static.gif)

### Content
- [altec](altec/index.htm)
- [Carver](Carver/index.htm)
- [SL-7](SL-7/index.htm)
