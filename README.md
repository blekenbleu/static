`static`
## Static content for GitHub Pages
Content (e.g. images, PDFs, HTML) in GitHub Pages repositories consume 3x storage
- original
- copied into: ./_site/
- also in: .git/objects/pack/

Moving static content to a separate GitHub repository reduces:
- storage
- GitHub Pages build time  

### Status
- Deployed as [`/static/` folder](https://blekenbleu.github.io/static/)
 to [GitHub Pages](https://blekenbleu.github.io/):  
    ![settings](static.gif)  
- This technique is sometimes called a [GitHub Pages **project** site](https://docs.github.com/en/pages/getting-started-with-github-pages/about-github-pages#types-of-github-pages-sites).  
- `.nojekyll` stops *default* GitHub Action  

