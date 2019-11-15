using lab2_1.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace lab2_1.Controllers
{
    public class ArticleController : Controller
    {
        // GET: afisarea tuturor articolelor
        [HttpGet]
        [ActionName("listare")]
        public ActionResult Index() {
            Article[] articles = GetArticles();
            ViewBag.Articles = articles;
            return View("Index");
        }

        // GET: afisarea articolului cu IDul id
        [HttpGet]
        public ActionResult Show(int id) {
            Article[] articles = GetArticles();

            try {
                ViewBag.Article = articles[id];
                return View();
            } catch (Exception e) {
                ViewBag.ErrorMessage = e.Message;
                return View("Error");
            }

            return View();
        }

        // GET: afisam formularul in care se introduc datele noului articol
        [HttpGet]
        public ActionResult New() {
            return View();
        }

        [HttpPost]
        public ActionResult New(Article article) {
            // Creare articol
            return View("NewPostMethod");
        }

        // GET: afisarea datelor corespunzatoare articolului cu IDul id
        [HttpGet]
        public ActionResult Edit(int id) {
            ViewBag.Id = id;
            return View("EditPutMethod");
        }

        [HttpPut]
        public ActionResult Edit(Article article) {
            // Editare articol
            return View();
        }

        // DELETE: stergerea articolului cu IDul id
        [HttpDelete]
        public ActionResult Delete(int id) {
            // Stergere articol
            return View();
        }

        public Article[] GetArticles() {
            Article[] articles = new Article[3];

            for (int i = 0; i < 3; ++i) {
                Article article = new Article();
                article.Id = 1;
                article.Title = "Articol " + (i + 1).ToString();
                article.Content = "Continut articol " + (i + 1).ToString();
                article.Date = DateTime.Now;

                articles[i] = article;
            }

            return articles;
        }
    }
}